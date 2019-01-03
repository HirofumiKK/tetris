#include "Game.h"

const int WELL_WIDTH  = 10;
const int WELL_HEIGHT = 18;

int main()
{
    Game g(WELL_WIDTH, WELL_HEIGHT);
    g.play();
}

#include "Piece.h"
#include <random>

PieceType chooseRandomPieceType()
{
    static std::random_device aRandomDevice;
    static std::default_random_engine generator(aRandomDevice());
    std::uniform_int_distribution<> distro(0, NUM_PIECE_TYPES-1);
    return static_cast<PieceType>(distro(generator));
}


// 3.1: class Piece has private variables
// 3.2: class Piece's all private variables are now public
// 3.3: submitted project, sorta complete but not really
//      some issues: boundary issues, incomplete foamBomb
// 3.4: complete version completed for my sake
