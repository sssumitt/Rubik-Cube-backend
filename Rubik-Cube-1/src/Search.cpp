#include "Cube.h"
#include "PruningTable.h"
#include "MoveTable.h"
#include "CoordCube.h"
#include "FaceCube.h"
#include "Search.h"
#include "PruningTable.h"

#include <time.h>

#include <iostream>


MoveTable moveTable;
PruningTable pruningTable;



Search::Search(std::string scrambledFaceCube) {
    this->scrambledFaceCube = scrambledFaceCube;

    for (int i = 0; i < 31; i++) {
        ax[i] = 0;
        po[i] = 0;
        flip[i] = 0;
        twist[i] = 0;
        slice[i] = 0;
        parity[i] = 0;
        URFtoDLF[i] = 0;
        FRtoBR[i] = 0;
        URtoUL[i] = 0;
        UBtoDF[i] = 0;
        URtoDF[i] = 0;
        minDistPhase1[i] = 0;
        minDistPhase2[i] = 0;

    }
 
}


std::string Search::solToStr(int length, int depthPhase1) {
    std::string move = "URFDLB" ;

    std::string s = "";
     for (int i = 0; i < length; i++) {
        s += move[ax[i]];
        
        switch (po[i]) {
        case 1:
            s += ' ';
            break;
        case 2:
            s += '2';
            s += ' ';
            break;
        case 3:
            s += '\'';
            s += ' ';
            break;
        }
        if (i == depthPhase1 - 1) {
            s += '.';
            s += ' ';
        }
    }
    return s;
}

std::string Search::ida_star_phase1(int maxDepth, long timeOut, int useSeparator) {

    FaceCube faceCube;
    faceCube.updateFacelets_string(scrambledFaceCube);
    Cube cube = faceCube.getCube();
    CoordCube cc;
    cc.set_CoordCube(cube);
   

    // cube.display();
    // faceCube.printFacelets(cube);
    // cc.displayCoord(cube);




    po[0] = 0 ; 
    ax[0] = 0 ;
    flip[0] = cc.flip; ;
    twist[0] = cc.twist;
    parity[0] = cc.parity;
    slice[0] = cc.FRtoBR / 24;
    URFtoDLF[0] = cc.URFtoDLF;
    FRtoBR[0] = cc.FRtoBR;
    URtoUL[0] = cc.URtoUL;
    UBtoDF[0] = cc.UBtoDF;


    minDistPhase1[1] = 1;

    int mv = 0, n = 0;
    int depthPhase1 = 1;
    int busy = 0;

    time_t tStart = time(NULL);


// search loop
    while(true) {
        // move selection and pruning
           do {
            if ((depthPhase1 - n) > minDistPhase1[n + 1] && !busy) {
                if (ax[n] == 0 || ax[n] == 3) {
                    ax[++n] = 1;  // Initialize with R
                } else {
                    ax[++n] = 0;  // Initialize with U
                }
                po[n] = 1;
            } else if (++po[n] > 3) {
                po[n] = 1;
                do {
                    if (++ax[n] > B) { // B = 5
                        if (difftime(time(nullptr), tStart) > timeOut) {
                            return "";
                        }
                        if (n == 0) {
                            if (depthPhase1 >= maxDepth) {
                                return "";
                            } else {
                                depthPhase1++;
                                ax[n] = 0;
                                po[n] = 1;
                                busy = 0;
                                break;
                            }
                        } else {
                            --n;
                            busy = 1;
                            break;
                        }
                    } else {
                        po[n] = 1;
                        busy = 0;
                    }
                } while (n != 0 && (ax[n - 1] == ax[n] || ax[n - 1] - 3 == ax[n]));
            } else {
                busy = 0;
            }
        } while (busy);
    
        // compute new coordinates and new minDistPhase1
        mv = 3 * ax[n] + po[n] - 1;  // move index
   
        // update coordinates using current move
        flip[n + 1] = static_cast<int>(moveTable.flipMove[flip[n]][mv]);
        twist[n + 1] = static_cast<int>(moveTable.twistMove[twist[n]][mv]);
        slice[n + 1] = static_cast<int>(moveTable.FRtoBR_Move[static_cast<short>(slice[n]) * 24][mv]) / 24;

   

        signed char flipPruning = pruningTable.getPruning(PruningTable::Slice_Flip_Prun, N_SLICE1 * flip[n + 1] + slice[n + 1],"Slice_Flip_Prun :");
        signed char twistPruning = pruningTable.getPruning(PruningTable::Slice_Twist_Prun, N_SLICE1 * twist[n + 1] + slice[n + 1],"Slice_Twist_Prun :");

    
        minDistPhase1[n + 1] = static_cast<int>(std::max(flipPruning, twistPruning));


        // std::cout <<" " << n  << " " << depthPhase1 << " " << minDistPhase1[n] << std::endl;


        // Check if the current state reaches the H subgroup

        if(minDistPhase1[n+1] == 0 && n >= depthPhase1 - 5) {
            minDistPhase1[n + 1] = 10; // prevent further pruning
             
            // Search phase 2
            
            if (n == depthPhase1 -1 ) {
                int s = ida_star_phase2(depthPhase1, maxDepth);
                if(s >= 0) {
                    // Validate the solution depth and move sequence
                    if(s == depthPhase1 || (ax[depthPhase1 - 1] != ax[depthPhase1] && ax[depthPhase1 - 1] != (ax[depthPhase1] + 3))) {
                                // Convert the move sequence to a string
                            std::string res = useSeparator ? solToStr( s, depthPhase1) : solToStr(s, -1);
                            return res;
                    }
                }
            }
        }
    }
    return "";  // No solution found
}


int Search::ida_star_phase2(int depthPhase1, int maxDepth) {
    
    int mv = 0, d1 = 0, d2 = 0, i;

    int maxDepthPhase2 = std::min(10, maxDepth - depthPhase1);

    int depthPhase2;
    int n;
    int busy;

    // Update URFtoDLF, FRtoBR, parity for moves in phase 1
    for (i = 0; i < depthPhase1; i++) {
        mv = 3 * ax[i] + po[i] - 1;
        URFtoDLF[i + 1] = static_cast<int>( MoveTable::URFtoDLF_Move[URFtoDLF[i]][mv]);
        FRtoBR[i + 1]   = static_cast<int>( MoveTable::FRtoBR_Move[FRtoBR[i]][mv]    );
        parity[i + 1]   = static_cast<int>( MoveTable::parityMove[parity[i]][mv]     );
    }

    // Calculate d1
    d1 = pruningTable.getPruning(
        PruningTable::Slice_URFtoDLF_Parity_Prun,
        (N_SLICE2 * URFtoDLF[depthPhase1] + FRtoBR[depthPhase1]) * 2 + parity[depthPhase1],"Slice_URFtoDLF_Parity_Prun :"
    );

    if (d1 > maxDepthPhase2) {
        return -1;
    }

    // Update URtoUL and UBtoDF for moves in phase 1
    for (i = 0; i < depthPhase1; i++) {
        mv = 3 * ax[i] + po[i] - 1;
        URtoUL[i + 1] = static_cast<int>( MoveTable::URtoUL_Move[URtoUL[i]][mv]);
        UBtoDF[i + 1] = static_cast<int>( MoveTable::UBtoDF_Move[UBtoDF[i]][mv]);
    }

    // Merge URtoUL and UBtoDF to get URtoDF[depthPhase1]
    URtoDF[depthPhase1] = static_cast<int> (MoveTable::MergeURtoULandUBtoDF[URtoUL[depthPhase1]][UBtoDF[depthPhase1]]);

    // std::cout<< "URtoDF[depthPhase1] : " << URtoDF[depthPhase1] << " " <<depthPhase1 << std::endl;

    
    int idx = N_SLICE2 * URtoDF[depthPhase1] + FRtoBR[depthPhase1] * 2 + parity[depthPhase1] ;
    // Calculate d2
    d2 = pruningTable.getPruning(
        PruningTable::Slice_URtoDF_Parity_Prun,
        idx ,"Slice_URtoDF_Parity_Prun :"
    );
  
    
    if (d2 > maxDepthPhase2) {
        return -1;
    }

    // Check if already solved
    if ((minDistPhase2[depthPhase1] = std::max(d1, d2)) == 0) {
        return depthPhase1;
    }

    // Initialize for phase 2 search
    depthPhase2 = 1;
    n = depthPhase1;
    busy = 0;
    po[depthPhase1] = 0;
    ax[depthPhase1] = 0;
    minDistPhase2[n + 1] = 1; // else failure for depthPhase2=1, n=0

    // Start phase 2 search
    do {
        do {
            if ((depthPhase1 + depthPhase2 - n) > minDistPhase2[n + 1] && !busy) {
                // Initialize next move
                if (ax[n] == 0 || ax[n] == 3) {
                    ax[++n] = 1;
                    po[n] = 2;
                } else {
                    ax[++n] = 0;
                    po[n] = 1;
                }
            } else if ((ax[n] == 0 || ax[n] == 3) ? (++po[n] > 3) : ((po[n] += 2) > 3)) {
                do {
                    // Increment axis
                    if (++ax[n] > 5) {
                        if (n == depthPhase1) {
                            if (depthPhase2 >= maxDepthPhase2) {
                                return -1;
                            } else {
                                depthPhase2++;
                                ax[n] = 0;
                                po[n] = 1;
                                busy = 0;
                                break;
                            }
                        } else {
                            --n;
                            busy = 1;
                            break;
                        }
                    } else {
                        if (ax[n] == 0 || ax[n] == 3)
                            po[n] = 1;
                        else
                            po[n] = 2;
                        busy = 0;
                    }
                } while (n != depthPhase1 && (ax[n - 1] == ax[n] || ax[n - 1] - 3 == ax[n]));
            } else {
                busy = 0;
            }
        } while (busy);

        // Compute new coordinates and new minDistPhase2
        mv = 3 * ax[n] + po[n] - 1;
        
        URFtoDLF[n + 1] = MoveTable::URFtoDLF_Move[URFtoDLF[n]][mv];
        FRtoBR[n + 1] = MoveTable::FRtoBR_Move[FRtoBR[n]][mv];
        parity[n + 1] = MoveTable::parityMove[parity[n]][mv];
        URtoDF[n + 1] = MoveTable::URtoDF_Move[URtoDF[n]][mv];

        int prune1 = pruningTable.getPruning(
            PruningTable::Slice_URtoDF_Parity_Prun,
            (N_SLICE2 * URtoDF[n + 1] + FRtoBR[n + 1]) * 2 + parity[n + 1],"Slice_URtoDF_Parity_Prun :"
        );
        int prune2 = pruningTable.getPruning(
            PruningTable::Slice_URFtoDLF_Parity_Prun,
            (N_SLICE2 * URFtoDLF[n + 1] + FRtoBR[n + 1]) * 2 + parity[n + 1],"Slice_URFtoDLF_Parity_Prun :"
        );

        minDistPhase2[n + 1] = std::max(prune1, prune2);

    } while (minDistPhase2[n + 1] != 0);
    // std::cout<< "depthPhase1 : " << depthPhase1 << " depthPhase2 : " << depthPhase2 << std::endl;
    return depthPhase1 + depthPhase2;
}
