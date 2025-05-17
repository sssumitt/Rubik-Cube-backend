#include "FaceCube.h"
#include <iostream>
// Edge mappings
const FaceCube::EdgeMapping FaceCube::edgeMappings[12] = {
    {U, 5, R, 1},  // UR  0
    {U, 7, F, 1},  // UF  1
    {U, 3, L, 1},  // UL  2
    {U, 1, B, 1},  // UB  3

    {D, 5, R, 7},  // DR  4
    {D, 1, F, 7},  // DF  5
    {D, 3, L, 7},  // DL  6
    {D, 7, B, 7},  // DB  7

    {F, 5, R, 3},  // FR  8
    {F, 3, L, 5},  // FL  9

    {B, 5, L, 3},  // BL 10
    {B, 3, R, 5},  // BR 11
};

const FaceCube::CornerMapping FaceCube::cornerMappings[8] = {
    {U, 8, R, 0, F, 2}, // URF  0
    {U, 6, F, 0, L, 2}, // UFL  1
    {U, 0, L, 0, B, 2}, // ULB  2
    {U, 2, B, 0, R, 2}, // UBR  3

    {D, 2, F, 8, R, 6}, // DFR  4

    {D, 0, L, 8, F, 6}, // DLF  5

    {D, 6, B, 8, L, 6}, // DBL  6

    {D, 8, R, 8, B, 6}  // DRB  7
    
};

// Edge colors in solved state
//  w, r, g, y, o, b
const char FaceCube::edgeColors[12][2] = {
    {'W', 'R'}, // UR
    {'W', 'G'}, // UF
    {'W', 'O'}, // UL
    {'W', 'B'}, // UB

    {'Y', 'R'}, // DR
    {'Y', 'G'}, // DF
    {'Y', 'O'}, // DL
    {'Y', 'B'}, // DB

    {'G', 'R'}, // FR
    {'G', 'O'}, // FL

    {'B', 'O'}, // BL
    {'B', 'R'}, // BR
};

// Corner colors in solved state
const char FaceCube::cornerColors[8][3] = {
    {'W', 'R', 'G'}, // URF
    {'W', 'G', 'O'}, // UFL
    {'W', 'O', 'B'}, // ULB
    {'W', 'B', 'R'}, // UBR
    {'Y', 'G', 'R'}, // DFR
    {'Y', 'O', 'G'}, // DLF
    {'Y', 'B', 'O'}, // DBL
    {'Y', 'R', 'B'}, // DRB
};

FaceCube::FaceCube() {
    // Initialize facelets to default colors
    for (int face = U; face <= B; ++face) {
        for (int index = 0; index < 9; ++index) {
            facelets[face][index] = colors[face];
        }
    }

}

void FaceCube::updateFacelets(const Cube &cube ) {

    // Reset center facelets 
    for (int face = 0; face < 6; ++face) {
        facelets[face][4] = colors[face] ;
    }

    // Update edges 
    
    for(int i = 0 ; i< EDGE_COUNT ; i++) {

        int pos = cube.edgePositions[i] ; // get the edge at ith pos 
        char ori = cube.edgeOrientations[i] ; 
        // std::cout<< "pos : " << pos << " ori : " << static_cast<int>(ori) << std::endl;
        

        EdgeMapping em_i  = edgeMappings[i] ;

        char c1 = edgeColors[pos][0] ; 
        char c2 = edgeColors[pos][1]  ; 

        if(static_cast<int>(ori) == 1)  {
            char temp = c1 ; 
            c1 = c2 ; 
            c2 = temp ; 
        }

        facelets[em_i.face1][em_i.index1]   = c1 ;
        facelets[em_i.face2][em_i.index2]   = c2 ;   

    }
    
    // Update corners
    for (int i = 0; i < CORNER_COUNT ; ++i) {
        int pos = cube.cornerPositions[i];         
        char ori = cube.cornerOrientations[i];
      
        // std::cout<< "pos : " << pos << " ori : " << static_cast<int>(ori)  << std::endl;

        CornerMapping em_i = cornerMappings[i];

        char c1 = cornerColors[pos][0];
        char c2 = cornerColors[pos][1];
        char c3 = cornerColors[pos][2];

        //clockwise 
        if(static_cast<int>(ori) == 1) {
            char temp = c1 ; 
            c1 = c3 ; 
            c3 = c2 ; 
            c2 = temp ; 
        }
        //counter clockwise   
        if(static_cast<int>(ori) == 2) {
            char temp  = c1 ; 
            c1 = c2 ; 
            c2 = c3 ; 
            c3 = temp ; 
        }

        facelets[em_i.face1][em_i.index1] = c1 ; 
        facelets[em_i.face2][em_i.index2] = c2 ;
        facelets[em_i.face3][em_i.index3] = c3 ;
    }

}

void FaceCube::updateFacelets_string(const std::string &inputFacelets){
    int i = 0 ; 
    for(int face = 0 ; face < 6 ; face++) {
        for(int index = 0 ; index < 9 ; index++) {
            facelets[face][index] = inputFacelets[i++] ; 
        }
    }

}


// Helper function to find edge
std::tuple<int, char> FaceCube::findEdge(char color1, char color2) const {
    for (int i = 0; i < EDGE_COUNT; ++i) {
 
        if ((edgeColors[i][0] == color1 && edgeColors[i][1] == color2)) {
            return std::make_tuple(i, 0); // Position, Orientation 0
        }
        if ((edgeColors[i][0] == color2 && edgeColors[i][1] == color1)) {
            return std::make_tuple(i, 1); // Position, Orientation 1
        }
    }
    throw std::invalid_argument("Edge not found");
}

// Helper function to find corner
std::tuple<int, char> FaceCube::findCorner(char color1, char color2, char color3) const {
    for (int i = 0; i < CORNER_COUNT; ++i) {
        // Check all three possible orientations
        if ((cornerColors[i][0] == color1 && cornerColors[i][1] == color2 && cornerColors[i][2] == color3)) {
            return std::make_tuple(i, 0); // Position, Orientation 0
        }
        if ((cornerColors[i][0] == color2 && cornerColors[i][1] == color3 && cornerColors[i][2] == color1)) {
            return std::make_tuple(i, 1); // Position, Orientation 1
        }
        if ((cornerColors[i][0] == color3 && cornerColors[i][1] == color1 && cornerColors[i][2] == color2)) {
            return std::make_tuple(i, 2); // Position, Orientation 2
        }
    }
    throw std::invalid_argument("Corner not found");
}
Cube FaceCube::getCube() const { 
    Cube cube; 

    // Edge initialization 
    for(int i = 0; i < EDGE_COUNT; i++) {
       EdgeMapping mapping = edgeMappings[i];

        char color1 = facelets[mapping.face1][mapping.index1];
        char color2 = facelets[mapping.face2][mapping.index2];
        
        int pos ;
        char ori;

        try {
            std::tie(pos, ori) = findEdge(color1, color2);
            cube.edgePositions[i] = pos;
            cube.edgeOrientations[i] = ori;
        }
        catch (const std::invalid_argument& e) {
            throw std::runtime_error("Unsolvable cube: " + std::string(e.what()));
        }
    }

    // Corner initialization
    for(int i = 0; i < CORNER_COUNT; i++) {
        CornerMapping mapping = cornerMappings[i];

        char color1 = facelets[mapping.face1][mapping.index1];
        char color2 = facelets[mapping.face2][mapping.index2];
        char color3 = facelets[mapping.face3][mapping.index3];

        int pos;
        char ori;

        try {
            std::tie(pos, ori) = findCorner(color1, color2, color3);
            cube.cornerPositions[i] = pos;
            cube.cornerOrientations[i] = ori;
        }
        catch (const std::invalid_argument& e) {
            throw std::runtime_error("Unsolvable cube: " + std::string(e.what()));
        }
    }

    return cube;
}


std::string FaceCube::colorToString(char color) const {
    switch (color) {

        case 'W': return "\033[1;37mW\033[0m"; // White
        case 'R': return "\033[1;31mR\033[0m"; // Red
        case 'G': return "\033[1;32mG\033[0m"; // Green
        case 'Y': return "\033[1;33mY\033[0m"; // Yellow
        case 'O': return "\033[1;35mO\033[0m"; // Orange-purple
        case 'B': return "\033[1;34mB\033[0m"; // Blue

        default: return "?";
    }
}

std::string FaceCube::getFacelets(const Cube &cube) {
    updateFacelets(cube);

    std::string faceletString;

    for (int face = U; face <= B; ++face) {
        for (int index = 0; index < 9; ++index) {
            faceletString += facelets[face][index] ;
        }
    }
    return faceletString;
}

void FaceCube::printFacelets(const Cube &cube) {
    updateFacelets(cube) ;

    // Print Up face
    std::cout << "    " << colorToString(facelets[U][0]) << colorToString(facelets[U][1]) << colorToString(facelets[U][2]) << "\n";
    std::cout << "    " << colorToString(facelets[U][3]) << colorToString(facelets[U][4]) << colorToString(facelets[U][5]) << "\n";
    std::cout << "    " << colorToString(facelets[U][6]) << colorToString(facelets[U][7]) << colorToString(facelets[U][8]) << "\n";

    // Print Left, Front, Right, Back faces
    for (int row = 0; row < 3; ++row) {
        std::cout << colorToString(facelets[L][row * 3 + 0]) << colorToString(facelets[L][row * 3 + 1]) << colorToString(facelets[L][row * 3 + 2]) << " ";
        std::cout << colorToString(facelets[F][row * 3 + 0]) << colorToString(facelets[F][row * 3 + 1]) << colorToString(facelets[F][row * 3 + 2]) << " ";
        std::cout << colorToString(facelets[R][row * 3 + 0]) << colorToString(facelets[R][row * 3 + 1]) << colorToString(facelets[R][row * 3 + 2]) << " ";
        std::cout << colorToString(facelets[B][row * 3 + 0]) << colorToString(facelets[B][row * 3 + 1]) <<  colorToString(facelets[B][row * 3 + 2])<< "\n";
    }

    // Print Down face
    std::cout <<"    " << colorToString(facelets[D][0]) << colorToString(facelets[D][1]) << colorToString(facelets[D][2]) << "\n";
    std::cout <<"    " << colorToString(facelets[D][3]) << colorToString(facelets[D][4]) << colorToString(facelets[D][5]) << "\n";
    std::cout <<"    " << colorToString(facelets[D][6]) << colorToString(facelets[D][7]) << colorToString(facelets[D][8]) << "\n";

    std::cout << "\n";

}
