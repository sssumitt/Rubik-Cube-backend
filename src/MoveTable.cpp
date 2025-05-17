#include "MoveTable.h"
#include "CoordCube.h"
#include "Cube.h"

#include <fstream>
#include <iostream>
#include <sstream>

// Initialize static member variables
std::array<std::array<short, N_MOVE>, N_TWIST> MoveTable::twistMove;
std::array<std::array<short, N_MOVE>, N_FLIP> MoveTable::flipMove;
std::array<std::array<short, N_MOVE>, N_FRtoBR> MoveTable::FRtoBR_Move;
std::array<std::array<short, N_MOVE>, N_URFtoDLF> MoveTable::URFtoDLF_Move;
std::array<std::array<short, N_MOVE>, N_URtoDF> MoveTable::URtoDF_Move;
std::array<std::array<short, N_MOVE>, N_URtoUL> MoveTable::URtoUL_Move;
std::array<std::array<short, N_MOVE>, N_UBtoDF> MoveTable::UBtoDF_Move;
std::array<std::array<short, 336>, 336> MoveTable::MergeURtoULandUBtoDF;

std::array<std::array<short, N_MOVE>, N_PARITY> MoveTable::parityMove= {
    std::array<short, N_MOVE>{ 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 },
    std::array<short, N_MOVE>{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 }
};

// Constructor
MoveTable::MoveTable() {
    loadMoveTables("Table");

}

// Method to load move tables from binary files
bool MoveTable::loadMoveTables(const std::string& directory) {
    bool success = true;
    success &= loadMoveTableBinary(directory + "/twistMove", twistMove[0].data(), N_TWIST * N_MOVE);
    success &= loadMoveTableBinary(directory + "/flipMove", flipMove[0].data(), N_FLIP * N_MOVE);
    success &= loadMoveTableBinary(directory + "/FRtoBR_Move", FRtoBR_Move[0].data(), N_FRtoBR * N_MOVE);
    success &= loadMoveTableBinary(directory + "/URFtoDLF_Move", URFtoDLF_Move[0].data(), N_URFtoDLF * N_MOVE);
    success &= loadMoveTableBinary(directory + "/URtoDF_Move", URtoDF_Move[0].data(), N_URtoDF * N_MOVE);
    success &= loadMoveTableBinary(directory + "/URtoUL_Move", URtoUL_Move[0].data(), N_URtoUL * N_MOVE);
    success &= loadMoveTableBinary(directory + "/UBtoDF_Move", UBtoDF_Move[0].data(), N_UBtoDF * N_MOVE);
    success &= loadMoveTableBinary(directory + "/MergeURtoULandUBtoDF", MergeURtoULandUBtoDF[0].data(), 336 * 336);

    return success;
}

bool MoveTable::loadMoveTableBinary(const std::string& filename, short* data, size_t size) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening move table file: " << filename << std::endl;
        return false;
    }

    // Read the data
    file.read(reinterpret_cast<char*>(data), size * sizeof(short));

    if (!file) {
        std::cerr << "Error reading move table from file: " << filename << std::endl;
        return false;
    }

    return true;
}

