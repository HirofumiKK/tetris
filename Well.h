#ifndef WELL_INCLUDED
#define WELL_INCLUDED

#include "Piece.h"

class Well
{
public:
    Well(int width, int height, PieceType p, int orientation, int x, int y);
    ~Well();
    void displayWell(Screen& screen, int x, int y);
    bool isFilled(int x, int y) const;
    bool canGoDown() const;
    bool canGoLeft() const;
    bool canGoRight() const;
    void displayPiece(Screen& screen, int type, int orientation, int x, int y) const;
    void erasePiece(Screen& screen);
    void goDown(Screen& screen);
    void goLeft(Screen& screen);
    void goRight(Screen& screen);
    void goBottom(Screen& screen);
    void rotate(Screen& screen);
    void rotateCrazy(Screen& screen);
    void becomeDollar(Screen& screen);
    bool gameOver();
    void setNewPiece(PieceType type, int orientation, int x, int y, PieceType next);
    int vaporize(Screen& screen);
    void vaporBomb(Screen& screen);
    //void foamBomb(Screen& screen, const int originalX, const int originalY, int currX, int currY);
    void foamBomb(Screen& screen);
    
private:
    int m_width;
    int m_height;
    char** m_well;
    Piece m_piece;
    Timer m_time;
};

#endif // WELL_INCLUDED
