#include "Game.h"
#include "MenuState.h"
#include "GameState.h"

#include <memory>
#include <iostream>


Game::Game(std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight)
: window { new sf::RenderWindow {sf::VideoMode { gameWidth, gameHeight }, GAME_TITLE} }, event {},
  running { true }, gameStates {}, currentState { MENU_STATE }
{
    // Place Possible Game States in States Vector

    //gameStates.push_back(std::make_unique<MenuState>());

    int* tmp{&currentState};

    State* ptr = new MenuState{window, tmp};
    gameStates.push_back(ptr);
    
    ptr = new GameState{tmp};
    gameStates.push_back(ptr);
}


// Functions //

// Start Game
void Game::startGame ()
{

    sf::Clock clock;

    // Main Game Loop, One Iteration is a Frame
    while ( running )
    {
        sf::Time frameDuration {clock.restart()};

        // Handle Events
        handleEvents();

        // Update Logic
        updateLogic(frameDuration);

        // Clear Frame
        window->clear(sf::Color(255, 255, 255));

        // Render Frame
        renderFrame(window);

        // Display Frame
        window->display();

        // Update Current State
        getNextState();

    }
}

// Handle Events
void Game::handleEvents()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        /*  Game Only Handles Events That Result in The Game Terminating
            as These Events are Independent of State
            Other Events Are Handled bt the Current Game State
        */
        {
        case sf::Event::Closed:
            window->close();
            running = false;
            break;

        default:
            // Let Current Game State Handle Event
            gameStates.at(currentState)->handleEvent(event);
            break;
        }
    }
}

// Update Game Logic
void Game::updateLogic(sf::Time const & frameDuration)
{
    gameStates.at(currentState)->updateLogic(frameDuration);
}


// Render Frame
void Game::renderFrame(sf::RenderWindow* window)
{
    gameStates.at(currentState)->renderFrame(*window);
}

void Game::getNextState()
{
    currentState = gameStates.at(currentState)->getNextState();
}
