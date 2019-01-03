#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include "UserInterface.h"

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

class Piece{
public:
    Piece(PieceType type, int orient, int x, int y);
    void displayNextPiece(Screen& screen, PieceType nextPiece, int x, int y);
    
    // accessors
    PieceType getCurrentType() const {return m_currentPiece;}
    int getOrientation() const {return m_orientation;}
    int getCurrentX() const {return m_currentX;}
    int getCurrentY() const {return m_currentY;}
    char getChar(int x, int y) const {return m_piece[m_currentPieceInt][m_orientation][x][y];}
    
//private:
    char m_piece[10][4][4][4];
    PieceType m_currentPiece;
    int m_currentPieceInt;
    PieceType m_nextPiece;
    int m_orientation;
    int m_currentX;
    int m_currentY;
    
    int pieceTypeToInt(PieceType t);
};

#endif // PIECE_INCLUDED
