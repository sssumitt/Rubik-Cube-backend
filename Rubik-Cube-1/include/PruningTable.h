#ifndef PRUNING_TABLE_H
#define PRUNING_TABLE_H

#include "CoordCube.h"
#include "Move.h"
#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class PruningTable {
public:
    // Constructors and Destructor
    PruningTable();

    // Methods to load pruning tables from files
    bool loadPruningTables(const std::string& directory);

    /**
     * @brief Retrieves a pruning value from a pruning table
     * 
     * @tparam Size The size of the pruning table array
     * @param table The pruning table array where each byte stores two 4-bit values
     * @param index The index into the pruning table
     * @return signed char The 4-bit pruning value at the specified index
     * 
     * @details
     * Each byte in the table stores two 4-bit pruning values to save memory.
     * For even indices, the lower 4 bits are returned.
     * For odd indices, the upper 4 bits are returned.
     */                                               
    template <size_t Size>
    signed char getPruning(const std::array<signed char, Size>& table, int index,std::string name) {
    // if(index < 0) {
    //     std::cerr << name <<"Error: Index is negative: " << index << std::endl;
    //     return -1; // Or handle the error as appropriate
    // }
    
    signed char res;

    if ((index & 1) == 0)
        res = (table[index / 2] & 0x0f);
    else
        res = ((table[index / 2] >> 4) & 0x0f);

    return res;
}

    // Pruning table for the permutation of corners and UD-slice edges in phase 2
    static std::array<signed char, N_SLICE2 * N_URFtoDLF * N_PARITY / 2> Slice_URFtoDLF_Parity_Prun;

    // Pruning table for the permutation of edges in phase 2
    static std::array<signed char, N_SLICE2 * N_URtoDF * N_PARITY / 2> Slice_URtoDF_Parity_Prun;

    // Pruning table for the twist of corners and the position of UD-slice edges in phase 1
    static std::array<signed char, N_SLICE1 * N_TWIST / 2 + 1> Slice_Twist_Prun;

    // Pruning table for the flip of edges and the position of UD-slice edges in phase 1
    static std::array<signed char, N_SLICE1 * N_FLIP / 2> Slice_Flip_Prun;

private:
    // Template function to load a pruning table from a binary file
    template <size_t Size>
    bool loadPruningTableBinary(const std::string& filename, std::array<signed char, Size>& table) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error opening pruning table file: " << filename << std::endl;
            return false;
        }

        // Read the entire table at once
        file.read(reinterpret_cast<char*>(table.data()), Size);

        if (!file) {
            std::cerr << "Error reading pruning table from file: " << filename << std::endl;
            return false;
        }

        return true;
    }
};

// Template methods must be defined in the header file

#endif // PRUNING_TABLE_H
