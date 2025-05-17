#ifndef MOVE_TABLE_H
#define MOVE_TABLE_H

#include "CoordCube.h"
#include <array>
#include <string>
#include <iostream>

class MoveTable {
public:
    // Constructors and Destructor
    MoveTable();

    // Methods to load move tables from files
   bool loadMoveTables(const std::string& directory) ;
   bool loadMoveTableBinary(const std::string& filename, short* data, size_t size);

 
    // Phase 1 Move Tables
    static std::array<std::array<short, N_MOVE>, N_TWIST> twistMove;       // Move table for the twists of the corners
    static std::array<std::array<short, N_MOVE>, N_FLIP> flipMove;         // Move table for the flips of the edges
    static std::array<std::array<short, N_MOVE>, N_PARITY> parityMove;     // Move table for corner/edge parity

    // Phase 1 and Phase 2 Shared Move Tables
    static std::array<std::array<short, N_MOVE>, N_FRtoBR> FRtoBR_Move;    // Move table for the four UD-slice edges (FR, FL, BL, BR)
    static std::array<std::array<short, N_MOVE>, N_URFtoDLF> URFtoDLF_Move;// Move table for corner permutations
    static std::array<std::array<short, N_MOVE>, N_URtoDF> URtoDF_Move;    // Move table for U-face and D-face edge permutations

    // Helper Move Tables for Phase 2
    static std::array<std::array<short, N_MOVE>, N_URtoUL> URtoUL_Move;    // Move table for the three edges UR, UF, and UL
    static std::array<std::array<short, N_MOVE>, N_UBtoDF> UBtoDF_Move;    // Move table for the three edges UB, DR, and DF

    // Merge table for URtoUL and UBtoDF at the start of Phase 2
    static std::array<std::array<short, 336>, 336> MergeURtoULandUBtoDF;
};

#endif // MOVE_TABLE_H
