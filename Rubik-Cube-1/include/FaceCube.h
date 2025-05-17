#ifndef FACECUBE_H
#define FACECUBE_H

#include "Edge.h"
#include "Cube.h"
#include "Corner.h"
#include "Move.h"
#include "Face.h"

#include <array>
#include <string>

// Forward declaration
class Cube;

class FaceCube {
public:
    FaceCube();

    // Update the facelets of the cube based on the current state of the cube
    void updateFacelets(const Cube &cube);
    void updateFacelets_string(const std::string &facelets);

    Cube getCube()const ;  

    // Get the current state of the cube as a string
    std::string getFacelets(const Cube &cube);

    std::string colorToString(char color) const;

    // Print the facelets of the cube
    void printFacelets(const Cube &cube);

private:
    std::array<std::array<char , 9>, 6> facelets; // 6 faces, each with 9 facelets
   
   
   

    struct EdgeMapping {
        int face1, index1; // First sticker 
        int face2, index2; // Second sticker
    };

    struct CornerMapping {
        int face1, index1;
        int face2, index2;
        int face3, index3;
    };
    static const EdgeMapping edgeMappings[12];
    static const CornerMapping cornerMappings[8];

    char colors[6] = {'W', 'R', 'G', 'Y', 'O', 'B'};// U-W R-R F-G D-Y L-O B-B

    std::tuple<int, char> findEdge(char color1, char color2) const;
    std::tuple<int, char> findCorner(char color1, char color2, char color3) const;

   
    static const char edgeColors[12][2];
    static const char cornerColors[8][3];

};

#endif // FACECUBE_H
