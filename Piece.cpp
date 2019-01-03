//
//  Piece.cpp
//  Project3
//
//  Created by Hirofumi Koichihara on 5/17/18.
//  Copyright © 2018 Hirofumi Koichihara. All rights reserved.
//

#include "Piece.h"
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;


// Definitions for all pieces
// [type][orientation][row][column]
const char PieceDef[10][4][4][4] =
{
    // PIECE_I
    {
        // orientation #0
        {
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', '#'},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orientation #1
        {
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '}
        },
        // orientation #2
        {
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', '#'},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orientation #3
        {
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '}
        }
    },
    // PIECE_L
    {
        // orientation #0
        {
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', ' '},
            {'#', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orientation #1
        {
            {' ', '#', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '}
        },
        // orientation #2
        {
            {' ', ' ', ' ', ' '},
            {' ', ' ', '#', ' '},
            {'#', '#', '#', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orientation #3
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '}
        }
    },
    // PIECE_J
    {
        // orientation #0
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', '#'},
            {' ', ' ', ' ', '#'},
            {' ', ' ', ' ', ' '}
        },
        // orientaiton #1
        {
            {' ', ' ', ' ', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', '#', '#', ' '},
        },
        // orientation #2
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', '#', '#'},
            {' ', ' ', ' ', ' '}
        },
        // orientation #3
        {
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '}
        }
    },
    // PIECE_T
    {
        // orientation #0
        {
            {' ', '#', ' ', ' '},
            {'#', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orientation #1
        {
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orientation #2
        {
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orientation #3
        {
            {' ', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },
    // PIECE_O
    {
        // orienation #0
        {
            {'#', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #1
        {
            {'#', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #2
        {
            {'#', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #3
        {
            {'#', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },
    // PIECE_S
    {
        // orienation #0
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #1
        {
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #2
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #3
        {
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', ' '}
        }
    },
    // PIECE_Z
    {
        // orienation #0
        {
            {' ', ' ', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #1
        {
            {' ', ' ', '#', ' '},
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #2
        {
            {' ', ' ', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #3
        {
            {' ', ' ', '#', ' '},
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },
    // PIECE_VAPOR
    {
        // orienation #0
        {
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #1
        {
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #2
        {
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #3
        {
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },
    // PIECE_FOAM
    {
        // orienation #0
        {
            
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
             
        },
        // orienation #1
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #2
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #3
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },
    // PIECE_CRAZY
    {
        // orienation #0
        {
            {'#', ' ', ' ', '#'},
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        // orienation #1
        {
            {' ', ' ', ' ', '#'},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', '#'}
        },
        // orienation #2
        {
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', ' '},
            {'#', ' ', ' ', '#'}
        },
        // orienation #3
        {
            {'#', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {'#', ' ', ' ', ' '}
        }
    }
};


Piece::Piece(PieceType type, int orient, int x, int y)
: m_currentPiece(type), m_orientation(orient), m_currentX(x), m_currentY(y)
{
    // copying definiton of each piece
    for(int a = 0 ; a < 10; a++){
        for(int b = 0; b < 4; b++){
            for(int c = 0; c < 4; c++){
                for(int d = 0; d < 4; d++){
                    m_piece[a][b][d][c] = PieceDef[a][b][c][d];
                }
            }
        }
    }
    
    m_nextPiece = chooseRandomPieceType();
    
    m_currentPieceInt = pieceTypeToInt(m_currentPiece);
}


void Piece::displayNextPiece(Screen& screen, PieceType nextPiece, int x, int y)
{
    int type = pieceTypeToInt(nextPiece);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            // traverse the row, and then moving to next row
            screen.gotoXY(x + i, y + j);
            screen.printChar(m_piece[type][0][i][j]);
        }
    }
}


int Piece::pieceTypeToInt(PieceType t)
{
    int result;
    if(t == PIECE_I)
        result = 0;
    else if(t == PIECE_L)
        result = 1;
    else if(t == PIECE_J)
        result = 2;
    else if(t == PIECE_T)
        result = 3;
    else if(t == PIECE_O)
        result = 4;
    else if(t == PIECE_S)
        result = 5;
    else if(t == PIECE_Z)
        result = 6;
    else if(t == PIECE_VAPOR)
        result = 7;
    else if(t == PIECE_FOAM)
        result = 8;
    else if(t == PIECE_CRAZY)
        result = 9;
    else
        result = rand() % 9;
    
    return result;
}
