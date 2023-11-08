#include "Game.h"

// Global Constants
std::string const GAME_TITLE  { "Game Test" };
unsigned    const GAME_WIDTH  { 640 };
unsigned    const GAME_HEIGHT { 320 };

int main()
{
    // Create Game Instance
    Game game { GAME_TITLE, GAME_WIDTH, GAME_HEIGHT };

    // Start Game
    game.startGame();

    return 0;
}
