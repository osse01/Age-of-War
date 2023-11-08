#include "Game.h"
// #include "MenuState.h"
#include "GameState.h"

#include <memory>


Game::Game(std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight)
: window { sf::VideoMode { gameWidth, gameHeight }, GAME_TITLE }, event {},
  running { true }, gameStates {}, currentState { GAME_STATE }
{
    // Place Possible Game States in States Vector

    //gameStates.push_back(std::make_unique<MenuState>());
//
    //State* ptr = new MenuState;
    //gameStates.push_back(ptr);
    
    State* ptr = new GameState;
    gameStates.push_back(ptr);

}


// Functions //

// Start Game
void Game::startGame ()
{

    // Main Game Loop, One Iteration is a Frame
    while ( running )
    {
        
        // Handle Events
        handleEvents();

        // Update Logic
        updateLogic();

        // Clear Frame
        window.clear(sf::Color(255, 255, 255));

        // Render Frame
        renderFrame();

        // Display Frame
        window.display();

        // Update Current State
        getNextState();

    }
}

// Handle Events
void Game::handleEvents()
{
    while (window.pollEvent(event))
    {
        switch (event.type)
        /*  Game Only Handles Events That Result in The Game Terminating
            as These Events are Independent of State
            Other Events Are Handled bt the Current Game State
        */
        {
        case sf::Event::Closed:
            window.close();
            break;

        default:
            // Let Current Game State Handle Event
            gameStates.at(currentState)->handleEvent(event);
            break;
        }
    }
}

// Update Game Logic
void Game::updateLogic()
{
    gameStates.at(currentState)->updateLogic();
}


// Render Frame
void Game::renderFrame()
{
    gameStates.at(currentState)->renderFrame();
}

void Game::getNextState()
{
    currentState = gameStates.at(currentState)->getNextState();
}
