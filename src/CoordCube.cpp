#include "CoordCube.h"
#include "Cube.h"
#include <iostream>

CoordCube::CoordCube() {
    // for solved cube 
    twist = 0;
    flip = 0;

    parity = 0;

    FRtoBR = 0;
    URFtoDLF = 0;
    URtoUL = 0;
    UBtoDF = 114;
    URtoDF = 0;

}
void CoordCube::displayCoord(const Cube &cube) {
 
    std::cout << "Twist : " << cube.getTwist() << std::endl;
    std::cout << "Flip : " << cube.getFlip() << std::endl;

    std::cout << "Parity : " << cube.cornerParity() << std::endl;
    
    std::cout << "FRtoBR : " << cube.getFRtoBR() << std::endl;
    std::cout << "URFtoDLF : " << cube.getURFtoDLF() << std::endl;
    std::cout << "URtoUL : " << cube.getURtoUL() << std::endl;
    std::cout << "UBtoDF : " << cube.getUBtoDF() << std::endl;
    std::cout << "URtoDF : " << cube.getURtoDF() << std::endl;
    
}

void CoordCube::set_CoordCube(Cube &cube) {
    twist = cube.getTwist();
    flip = cube.getFlip();
    parity = cube.cornerParity();
    FRtoBR = cube.getFRtoBR();
    URFtoDLF = cube.getURFtoDLF();
    URtoUL = cube.getURtoUL();
    UBtoDF = cube.getUBtoDF();
    URtoDF = cube.getURtoDF();
}

Cube CoordCube::getCube() const{
    Cube cube;
    cube.setTwist(twist);
    cube.setFlip(flip);
    cube.setFRtoBR(FRtoBR);
    cube.setURFtoDLF(URFtoDLF);
    cube.setURtoUL(URtoUL);
    cube.setUBtoDF(UBtoDF);
    cube.setURtoDF(URtoDF);
    return cube;
}
