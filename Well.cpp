#include "Well.h"


Well::Well(int width, int height, PieceType p, int orientation, int x, int y)
: m_width(width), m_height(height), m_piece(p, orientation, x, y)
{
    m_well = new char*[m_width + 2];
    for(int i = 0; i != m_width + 2; i++)
        m_well[i] = new char[height + 1];
}


Well::~Well()
{
    for(int i = 0; i != m_height + 1; i++)
        delete[] m_well[i];
    delete[] m_well;
}


void Well::displayWell(Screen& screen, int x, int y)
{
    // because x and y are empty space inside well,
    for(x = 0; x < m_width + 2; x++){
        for(y = 0; y < m_height + 1; y++){
            if(x == 0 || x == m_width + 1 || y == m_height){
                screen.gotoXY(x, y);
                screen.printChar('@');
                // also creating the boundary of the well into my own 2-d array
                m_well[x][y] = '@';
            }
        }
    }
}


bool Well::isFilled(int x, int y) const
{
    bool result = false;
    switch(m_well[x][y]){
        case '@':
        case '$':
        case '*':
            result = true;
            break;
    }
    return result;
}

// instead of making those special cases, maybe I could've just added another condition to check in my original loop
// additional checking: whether it exceeds the boarder
bool Well::canGoDown() const
{
    // I need to do something special for certain piece in certain orientation,
    // otherwise i would go over the boundary
    // special piece type and orientation
    // PIECE_I && # 1, 3
    // PIECE_T && # 3
    // PIECE_O && any #
    // PIECE_FOAM && any #
    // PIECE_CRAZY && # 3
    PieceType p = m_piece.m_currentPiece;
    int r = m_piece.m_orientation;
    if( (p == PIECE_I && (r == 1 || r == 3)) || (p == PIECE_T && r == 3) || (p == PIECE_O) || (p == PIECE_FOAM) || (p == PIECE_CRAZY && r == 3) ){
        // checking only the first two columns sicne the other two columns are empty
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 4; j++){
                if(m_piece.getChar(i, j) == '#' && isFilled(m_piece.m_currentX + i, m_piece.m_currentY + j + 1))
                    return false;
            }
        }
    }else if(p == PIECE_CRAZY && r == 1){ // PIECE_CRAZY && # 1
        for(int i = 2; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(m_piece.getChar(i, j) == '#' && isFilled(m_piece.m_currentX + i, m_piece.m_currentY + j + 1))
                    return false;
            }
        }
    }else{ // for most of pieces in most of orientations
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(m_piece.getChar(i, j) == '#' && isFilled(m_piece.m_currentX + i, m_piece.m_currentY + j + 1))
                    return false;
            }
        }
    }
    return true;
}


bool Well::canGoLeft() const
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(m_piece.getChar(i, j) == '#' && isFilled(m_piece.m_currentX + i - 1, m_piece.m_currentY + j))
                return false;
        }
    }
    return true;
}


bool Well::canGoRight() const
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(m_piece.getChar(i, j) == '#' && isFilled(m_piece.m_currentX + i + 1, m_piece.m_currentY + j))
                return false;
        }
    }
    return true;
}


void Well::displayPiece(Screen& screen, int type, int orientation, int x, int y) const
{
    // for the same reason as canGoDown function, I need to deal with special cases
    PieceType p = m_piece.m_currentPiece;
    int r = m_piece.m_orientation;
    if( (p == PIECE_I && (r == 1 || r == 3)) || (p == PIECE_T && r == 3) || (p == PIECE_O) || (p == PIECE_FOAM) || (p == PIECE_CRAZY && r == 3) ){
        // checking only the first two columns sicne the other two columns are empty
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 4; j++){
                if(m_piece.m_piece[type][orientation][i][j] == '#'){
                    screen.gotoXY(x + i, y + j);
                    screen.printChar('#');
                    m_well[x + i][y + j] = '#';
                }
            }
        }
    }else if(p == PIECE_CRAZY && r == 1){
        for(int i = 2; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(m_piece.m_piece[type][orientation][i][j] == '#'){
                    screen.gotoXY(x + i, y + j);
                    screen.printChar('#');
                    m_well[x + i][y + j] = '#';
                }
            }
        }
    }else{ // for most of pieces in most of orientations
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(m_piece.m_piece[type][orientation][i][j] == '#'){
                    screen.gotoXY(x + i, y + j);
                    screen.printChar('#');
                    // copying that display into my own virtual well
                    m_well[x + i][y + j] = '#';
                }
            }
        }
    }
}


// erase the entire piece that is moving right now
void Well::erasePiece(Screen& screen)
{
    // for the same reason as canGoDown function, I need to deal with special cases
    PieceType p = m_piece.m_currentPiece;
    int r = m_piece.m_orientation;
    if( (p == PIECE_I && (r == 1 || r == 3)) || (p == PIECE_T && r == 3) || (p == PIECE_O) || (p == PIECE_FOAM) || (p == PIECE_CRAZY && r == 3) ){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 4; j++){
                if(m_well[m_piece.m_currentX + i][m_piece.m_currentY + j] == '#'){
                    screen.gotoXY(m_piece.m_currentX + i, m_piece.m_currentY + j);
                    screen.printChar(' ');
                    // copying that into my own virtual well
                    m_well[m_piece.m_currentX + i][m_piece.m_currentY + j] = ' ';
                }
            }
        }
    }else if(p == PIECE_CRAZY && r == 1){
        for(int i = 2; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(m_well[m_piece.m_currentX + i][m_piece.m_currentY + j] == '#'){
                    screen.gotoXY(m_piece.m_currentX + i, m_piece.m_currentY + j);
                    screen.printChar(' ');
                    m_well[m_piece.m_currentX + i][m_piece.m_currentY + j] = ' ';
                }
            }
        }
    }else{ // for most of pieces in most of orientations
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(m_well[m_piece.m_currentX + i][m_piece.m_currentY + j] == '#'){
                    screen.gotoXY(m_piece.m_currentX + i, m_piece.m_currentY + j);
                    screen.printChar(' ');
                    // copying that into my own virtual well
                    m_well[m_piece.m_currentX + i][m_piece.m_currentY + j] = ' ';
                }
            }
        }
    }
}


void Well::goDown(Screen& screen)
{
    if(canGoDown()){
        erasePiece(screen);
        // shift everything down by one row
        displayPiece(screen, m_piece.m_currentPieceInt, m_piece.m_orientation, m_piece.m_currentX, m_piece.m_currentY + 1);
        m_piece.m_currentY++;
    }else{
        return ;
    }
}


void Well::goLeft(Screen& screen)
{
    if(canGoLeft()){
        erasePiece(screen);
        // shift everything to left by one column
        displayPiece(screen, m_piece.m_currentPieceInt, m_piece.m_orientation, m_piece.m_currentX - 1, m_piece.m_currentY);
        m_piece.m_currentX--;
    }else{
        return ;
    }
}


void Well::goRight(Screen& screen)
{
    if(canGoRight()){
        erasePiece(screen);
        // shift everything to right by one column
        displayPiece(screen, m_piece.m_currentPieceInt, m_piece.m_orientation, m_piece.m_currentX + 1, m_piece.m_currentY);
        m_piece.m_currentX++;
    }else{
        return ;
    }
}


void Well::goBottom(Screen& screen)
{
    if(canGoDown()){
        erasePiece(screen);
        while(canGoDown()){
            m_piece.m_currentY++;
        }
        displayPiece(screen, m_piece.m_currentPieceInt, m_piece.m_orientation, m_piece.m_currentX, m_piece.m_currentY);
    }else{
        return ;
    }
}


void Well::rotate(Screen& screen)
{
    int nextOrientation = m_piece.m_orientation + 1;
    if(m_piece.m_orientation == 3)
        nextOrientation = 0;
    // checking if rotation can be made with current position
    bool canRotate = true;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(m_piece.m_piece[m_piece.m_currentPieceInt][nextOrientation][m_piece.m_currentX + i][m_piece.m_currentY + j] == '#' && isFilled(m_piece.m_currentX + i, m_piece.m_currentY + j)){
                canRotate = false;
                goto endLoop;
            }
        }
    }
endLoop:
    if(canRotate){
        erasePiece(screen);
        displayPiece(screen, m_piece.m_currentPieceInt, nextOrientation, m_piece.m_currentX, m_piece.m_currentY);
        m_piece.m_orientation = nextOrientation;
    }else{
        return ;
    }
}


void Well::rotateCrazy(Screen& screen)
{
    int nextOrientation = m_piece.m_orientation - 1;
    if(m_piece.m_orientation == 0)
        nextOrientation = 3;
    // checking if rotation can be made with current position
    bool canRotate = true;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(m_piece.m_piece[m_piece.m_currentPieceInt][nextOrientation][m_piece.m_currentX + i][m_piece.m_currentY + j] == '#' && isFilled(m_piece.m_currentX + i, m_piece.m_currentY + j)){
                canRotate = false;
                goto endLoop;
            }
        }
    }
endLoop:
    if(canRotate){
        erasePiece(screen);
        displayPiece(screen, m_piece.m_currentPieceInt, nextOrientation, m_piece.m_currentX, m_piece.m_currentY);
        m_piece.m_orientation = nextOrientation;
    }else{
        return ;
    }
}


void Well::becomeDollar(Screen& screen)
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(m_piece.getChar(i, j) == '#'){
                screen.gotoXY(m_piece.m_currentX + i, m_piece.m_currentY + j);
                screen.printChar('$');
                // copying that display into my own virtual well
                m_well[m_piece.m_currentX + i][m_piece.m_currentY + j] = '$';
            }
        }
    }
}

bool Well::gameOver()
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(m_piece.m_piece[m_piece.m_currentPieceInt][0][4 + i][j] == '#' && (m_well[4 + i][j] == '$' || m_well[4 + i][j] == '*'))
                return true;
        }
    }
    return false;
}


void Well::setNewPiece(PieceType type, int orientation, int x, int y, PieceType next)
{
    m_piece.m_currentPiece = type;
    m_piece.m_orientation = orientation;
    m_piece.m_currentX = x;
    m_piece.m_currentY = y;
    m_piece.m_currentPieceInt = m_piece.pieceTypeToInt(type);
    m_piece.m_nextPiece = next;
}


int Well::vaporize(Screen& screen)
{
    int totalNumVaporized = 0;
    for(int vertical = 0; vertical < m_height + 1; vertical++){
        int numHrzFilled = 0;
        for(int horizontal = 1; horizontal < m_width + 2; horizontal++){
            char cell = m_well[horizontal][vertical];
            if( cell == '$' || cell == '*')
                numHrzFilled++;
        }
        if(numHrzFilled == m_width){// need to vaporize this row
            // special case: vaporizing the top/0th row
            if(vertical == 0){
                for(int i = 1; i < m_width + 2; i++){
                    screen.gotoXY(i, 0);
                    screen.printChar(' ');
                    m_well[i][0] = ' ';
                }
            }
            // every row above this row is shifted down by one,
            // starting from the row above the vaporized row
            for(int row = vertical; row >= 0; row--){
                for(int column = 1; column < m_width + 2; column++){
                    // go to the row that was vaporized
                    screen.gotoXY(column, row);
                    // copy down the above row
                    screen.printChar(m_well[column][row - 1]);
                    // copy down the result into my own well as well :)
                    m_well[column][row] = m_well[column][row - 1];
                }
            }
            totalNumVaporized++;
        }
    }
    return totalNumVaporized;
}

// this function is called only when PIECE_VAPOR settles down
void Well::vaporBomb(Screen& screen)
{
    // where the vapor bomb exists in coordinates
    // v1 = (m_piece.currentX + 1, m_piece.currentY)
    // v2 = (m_piece.currentX + 2, m_piece.currentY)
    for(int i = 0; i < 2; i++){
        for(int j = -2; j < 3; j++){
            // making sure not to vaporize at or beyond bounds
            // checking only for y-coordinates
            if(m_piece.m_currentY + j >= 0 && m_piece.m_currentY + j < m_height){
                // vaporizing first column
                screen.gotoXY(m_piece.m_currentX + 1, m_piece.m_currentY + j);
                screen.printChar(' ');
                m_well[m_piece.m_currentX + 1][m_piece.m_currentY + j] = ' ';
                
                // vaporizing second column
                screen.gotoXY(m_piece.m_currentX + 2, m_piece.m_currentY + j);
                screen.printChar(' ');
                m_well[m_piece.m_currentX + 2][m_piece.m_currentY + j] = ' ';
            }
        }
    }
}

/*
// this function is called only when PIECE_FOAM settles down
// I will pass into the current coordinate of bomb right after settling down:
//      (m_piece.m_currentX + 1, m_piece.m_currentY + 1)
void Well::foamBomb(Screen& screen, int originalX, int originalY, int currX, int currY)
{
    // right hand rule with memory?
    // north: (x, y - 1)
    // east: (x + 1, y)
    // south: (x, y + 1)
    // west: (x - 1, y)
    // current coordinate of bomb right after settling down:
    //      (m_piece.m_currentX + 1, m_piece.m_currentY + 1)
    screen.gotoXY(currX, currY);
    screen.printChar('*');
    m_well[currX][currY] = '*';
    
    // if nowhere to go, return nothing
    if(isFilled(currX, currY - 1) && isFilled(currX + 1, currY) && isFilled(currX, currY + 1) && isFilled(currX - 1, currY))
        return ;
    
    // conditions inside if statement
    // 1. valid rnage from the origin (with in the 5x5?)
    // 2. does not exceed bound/boarder of the well
    // 3. the path is actually open so i can move to that direction
    if(currX - originalX < 2 && currX + 1 < m_width + 1 && !isFilled(currX + 1, currY))
        return foamBomb(screen, originalX, originalY, currX + 1, currY);
    if(currY - originalY > -2 && currY - 1 >= 0 && !isFilled(currX, currY - 1))
        return foamBomb(screen, originalX, originalY, currX, currY - 1);
    if(currX - originalX > -2 && currX - 1 > 1 && !isFilled(currX - 1, currY))
        return foamBomb(screen, originalX, originalY, currX - 1, currY);
    if(currY - originalY < 2 && currY + 1 < m_height && !isFilled(currX, currY + 1))
        return foamBomb(screen, originalX, originalY, currX, currY + 1);
}
*/


void Well::foamBomb(Screen& screen)
{
    // where the bomb exists in the well
    int x = m_piece.m_currentX + 1;
    int y = m_piece.m_currentY + 1;
    for(int i = -2; i < 3; i++){
        for(int j = -2; j < 3; j++){
            // checking boundary
            if(x + i > 0 && x + i < m_width + 1 && y + j >= 0 && y + j < m_height){
                if(!isFilled(x + i, y + j)){
                    screen.gotoXY(x+i, y+j);
                    screen.printChar('*');
                    m_well[x+i][y+j] = '*';
                }
            }
        }
    }
}
