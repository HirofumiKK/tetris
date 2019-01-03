#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include <string>
// [Add other #include directives as necessary.]

class Game
{
public:
    Game(int width, int height);
    //~Game() {delete m_well;} not needed
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    // [Add other members as necessary.]
    
private:
    Well*   m_well;
    Screen  m_screen;
    int     m_level;
    int     m_previousLevel;
    Timer   m_time;
    int     m_score;
    int     m_rowsLeft;
    Piece   m_piece;
    int     m_width;
    int     m_height;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
