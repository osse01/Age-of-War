#include "Game.h"
#include "MenuState.h"
#include "GameState.h"

#include <memory>


Game::Game(std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight)
: window { sf::VideoMode { gameWidth, gameHeight }, GAME_TITLE },
    currentState { GAME_STATE }, running { true }
{
    // Place Possible Game States in States Vector
    //std::unique_ptr<MenuState> menuState = std::make_unique<MenuState>();
    gameStates.push_back(std::make_unique<MenuState>());

    gameStates.push_back(std::make_unique<GameState>());

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
        window.clear();

        // Render Frame
        renderFrame();

        // Display Frame
        window.display();

        // Update Current Frame
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

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
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
