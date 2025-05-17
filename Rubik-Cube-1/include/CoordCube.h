#ifndef COORDCUBE_H
#define COORDCUBE_H

#include "Cube.h"

// Forward declaration of Cube class
class Cube;

#define N_TWIST     2187
#define N_FLIP      2048
#define N_SLICE1    495
#define N_SLICE2    24
#define N_PARITY    2
#define N_URFtoDLF  20160
#define N_FRtoBR    11880
#define N_URtoUL    1320
#define N_UBtoDF    1320
#define N_URtoDF    20160
#define N_URFtoDLB  40320
#define N_URtoBR    479001600
#define N_MOVE      18

class CoordCube {
    public: 
        CoordCube();
        void set_CoordCube(Cube &cube);
        
        void displayCoord(const Cube &cube);
        Cube getCube() const;
        short twist;
        short flip;
        short parity;
        short FRtoBR;
        short URFtoDLF;
        short URtoUL;
        short UBtoDF;
        int URtoDF;

};

#endif