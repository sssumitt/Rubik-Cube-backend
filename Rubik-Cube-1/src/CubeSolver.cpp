#include "CubeSolver.h"
#include "MoveTable.h"
#include "PruningTable.h"
#include "FaceCube.h"
#include "Search.h"
#include <iostream>
#include <string>

std::string solveCube(const std::string& cubeState) {
    std::string scrambledCubeStr;

   
    Cube c;
	c.display();
    FaceCube fc;
    fc.updateFacelets(c);
    fc.printFacelets(c);
    
    

    Search search(cubeState);
    int maxDepth = 25;
    long timeOut = 1000;
    int useSeparator = 0;
    std::string solution = search.ida_star_phase1(maxDepth, timeOut, useSeparator);
    return solution;
}
