#include "Game.h"
#include <cmath>


const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

const int NEW_PIECE_X = 4;
const int NEW_PIECE_Y = 0;

PieceType type = chooseRandomPieceType();
int orientation = 0;

Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_previousLevel(1), m_score(0), m_rowsLeft(5), m_piece(type, orientation, NEW_PIECE_X, NEW_PIECE_Y), m_width(width), m_height(height)
{
    m_well = new Well(width, height, type, orientation, NEW_PIECE_X, NEW_PIECE_Y);
}

void Game::play()
{
    m_well->displayWell(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]
    
    
    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        m_screen.refresh();
        waitForEnter();
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    // The text "Next piece:" should be displayed at (16,3).
    m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
    m_screen.printString("Next piece:");
    
    // The current score should be displayed at (16,8) in the form "Score:" followed by five spaces followed by the score right-justified in a field seven characters wide.
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printString("Score:     ");
    
    // diplaying score
    // accounting for score bigger than 9
    // needs to initialize shiftScoreBy to zero since log10(0) is undefined
    int shiftScoreBy(0);
    if(m_score > 9)
        shiftScoreBy = shiftScoreBy = log10(m_score);
    m_screen.gotoXY(SCORE_X + 16 - shiftScoreBy, SCORE_Y);
    m_screen.printString( std::to_string(m_score));
    
    
    // The number of rows left that must be vaporized before the current level is completed should be displayed at (16,9) in the form: "Rows left: " followed by one space, followed by the number of rows left before the level is completed, right-justified in a field 7 characers wide.
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printString("Rows left:  ");
    
    // displaying rows left
    int shiftRowsLeftBy = log10(m_rowsLeft);
    m_screen.gotoXY(ROWS_LEFT_X + 16 - shiftRowsLeftBy, ROWS_LEFT_Y);
    m_screen.printString(std::to_string(m_rowsLeft));
    
    // The current level number should be displayed at (16,10) in the form "Level:" followed by five spaces, followed by the current level number, right-justified in a field seven charcaters wide.
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printString("Level:     ");
    
    // displaying level
    // doesn't need to initialize shiftLevelBy to 0 since m_level starts from 1
    int shiftLevelBy = log10(m_level);
    m_screen.gotoXY(LEVEL_X + 16 - shiftLevelBy, LEVEL_Y);
    m_screen.printString(std::to_string(m_level));
}

bool Game::playOneLevel()
{
    m_well->displayPiece(m_screen, m_piece.m_currentPieceInt, 0, NEW_PIECE_X, NEW_PIECE_Y);
    m_piece.displayNextPiece(m_screen, m_piece.m_nextPiece, NEXT_PIECE_X, NEXT_PIECE_Y);
    m_screen.refresh();
    
    while(!m_well->gameOver()){
        while(m_well->canGoDown()){
            m_time.start();
            while(m_time.elapsed() < fmax(1000-(100*(m_level-1)), 100)){
                char ch;
                if(getCharIfAny(ch)){
                    switch(ch){
                        case ARROW_DOWN:{
                            if(m_well->canGoDown())
                                m_well->goDown(m_screen);
                        }break;
                        case ARROW_LEFT:{
                            if(m_piece.m_currentPiece != PIECE_CRAZY && m_well->canGoLeft())
                                m_well->goLeft(m_screen);
                            else if(m_piece.m_currentPiece == PIECE_CRAZY && m_well->canGoRight())
                                m_well->goRight(m_screen);
                        }break;
                        case ARROW_RIGHT:{
                            if(m_piece.m_currentPiece != PIECE_CRAZY && m_well->canGoRight())
                                m_well->goRight(m_screen);
                            else if(m_piece.m_currentPiece == PIECE_CRAZY && m_well->canGoLeft())
                                m_well->goLeft(m_screen);
                        }break;
                        case ' ': m_well->goBottom(m_screen); break;
                        case ARROW_UP:{
                            if(m_piece.m_currentPiece != PIECE_CRAZY)
                            m_well->rotate(m_screen);
                        else
                            m_well->rotateCrazy(m_screen);
                    }break;
                        case 'q':
                        case 'Q':
                            return false;
                            break;
                            /*
                        case 'p':
                            waitForEnter();
                            break;
                             */
                    }
                    m_screen.refresh();
                }
            }
            m_well->goDown(m_screen);
            m_screen.refresh();
        }
        if(m_piece.m_currentPiece == PIECE_VAPOR)
            m_well->vaporBomb(m_screen);
        else if(m_piece.m_currentPiece == PIECE_FOAM)
            m_well->foamBomb(m_screen);
        else
            m_well->becomeDollar(m_screen);
        
        int numVaporized = m_well->vaporize(m_screen);
        if(numVaporized != 0){ // if one or more rows are vaporized
            m_rowsLeft -= numVaporized; // reduce m_rowsLeft
            switch(numVaporized){
                case 1: m_score += 100; break;
                case 2: m_score += 200; break;
                case 3: m_score += 400; break;
                case 4: m_score += 800; break;
                case 5: m_score += 1600; break;
            }
            displayStatus();
        }
        if(m_rowsLeft <= 0){
            m_level++;
            return true;
        }

        // prepare next piece
        m_piece.m_currentPiece = m_piece.m_nextPiece;
        m_piece.m_currentPieceInt = m_piece.pieceTypeToInt(m_piece.m_currentPiece);
        m_piece.m_nextPiece = chooseRandomPieceType();
        m_well->setNewPiece(m_piece.m_currentPiece, 0, NEW_PIECE_X, NEW_PIECE_Y, m_piece.m_nextPiece);
        
        // display the pieces
        m_well->displayPiece(m_screen, m_piece.m_currentPieceInt, 0, NEW_PIECE_X, NEW_PIECE_Y);
        m_piece.displayNextPiece(m_screen, m_piece.m_nextPiece, NEXT_PIECE_X, NEXT_PIECE_Y);
        m_screen.refresh();
    }
    return false; // game over
}
