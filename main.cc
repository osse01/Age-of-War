#include "Game.h"

// Global Constants
std::string const gameTitle  { "Game Test" };
unsigned    const gameWidth  { 640 };
unsigned    const gameHeight { 320 };

int main()
{
    // Create Game Instance
    Game game { gameTitle, gameWidth, gameHeight };

    // Start Game
    game.startGame();

    return 0;
}
