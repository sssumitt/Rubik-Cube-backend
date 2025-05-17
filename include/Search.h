#ifndef SEARCH_H
#define SEARCH_H

#include <MoveTable.h>
#include <PruningTable.h>
#include <Cube.h>
#include <CoordCube.h>
#include <FaceCube.h>
#include <string>

class Search { 
    public: 
        std::string scrambledFaceCube;
        Search(std::string scrmabledFaceCube );

        // converts the sol to string format using ax and po
        std::string solToStr(int length, int depthPhase1);

        // search path from given state to intermediate state returns Solution in string format 
        std::string ida_star_phase1(int maxDepth, long timeOut, int useSeparator);

        // search from intermediate state to solved state returns total depth  
        int ida_star_phase2(int depthPhase1, int maxDepth); 

        std::array<int, 31> ax;             // The axis of the move
        std::array<int, 31> po;             // The power of the move
        std::array<int, 31> flip;           // phase1 coordinates
        std::array<int, 31> twist;
        std::array<int, 31> slice;
        std::array<int, 31> parity;         // phase2 coordinates
        std::array<int, 31> URFtoDLF;
        std::array<int, 31> FRtoBR;
        std::array<int, 31> URtoUL;
        std::array<int, 31> UBtoDF;
        std::array<int, 31> URtoDF;
        std::array<int, 31> minDistPhase1;  // IDA* distance to goal estimations
        std::array<int, 31> minDistPhase2;
};

#endif