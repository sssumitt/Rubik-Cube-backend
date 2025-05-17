#ifndef CUBE_H 
#define CUBE_H 

#include "Move.h"
#include "Edge.h"
#include "Corner.h"

#include <string>
#include <array>

class Cube {
    public: 
        Cube() ; 
       
        void applyMove(const std::string& move) ;

        std::string moveToString(Move move) const;
      
        
        bool isSolved() const ;
    
        // Edge and corner positions and orientations
        std::array<int, EDGE_COUNT> edgePositions;
        std::array<char, EDGE_COUNT> edgeOrientations; // 0 or 1
        std::array<int, CORNER_COUNT> cornerPositions;
        std::array<char, CORNER_COUNT> cornerOrientations; // 0, 1, or 2

        short cornerParity()const ;
        short edgeParity() const;
        int Cnk(int n, int k) const; 
        // to coordCube
        short getTwist() const;
        short getFlip() const;    
        short getFRtoBR() const;
        short getURFtoDLF() const;
        int getURtoDF() const;
        short getURtoUL() const;
        short getUBtoDF() const;
        int getURFtoDLB() const;
        int getURtoBR() const;

        // from coordCube
        void setTwist( short twist ) ;
        void setFlip( short flip ) ;
        void setFRtoBR( short frToBr ) ;
        void setURFtoDLF( short urfToDlf ) ;
        void setURtoDF( int urToDf ) ;
        void setURtoUL( short urToUl ) ;
        void setUBtoDF( short ubToDf ) ;
        void setURFtoDLB(int idx);
        void setURtoBR(int idx) ;

        void display() const;
        int verify();

        // Rotate a specific face of the cube
        void rotateFace(const std::string& move);

};

#endif 