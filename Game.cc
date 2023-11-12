#include "Game.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"

#include <memory>
#include <iostream>


Game::Game(std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight)
:   window { new sf::RenderWindow { sf::VideoMode { gameWidth, gameHeight }, GAME_TITLE } },
    event {}, running { true }, states {}, currentState { MENU_STATE }, 
    currentStatePtr { &currentState }, music { new sf::Music }, nextState {}
{

    // Open Audio File
    std::string file{"Age-of-War-Theme-Song.ogg"};
    if (!music->openFromFile(file))
    {
        std::cout << "  >> Error: Could Not Find Audio File. Error in GameState::GameState()." << std::endl;
    }
    music->setVolume(50);
    music->setLoop(true);
    
    // Place Possible Game States in States Vector
    State* ptr = new MenuState{window, currentStatePtr, music};
    states.push_back(ptr);
    
    ptr = new GameState{window, currentStatePtr, music};
    states.push_back(ptr);

    ptr = new PauseState{window, currentStatePtr, music};
    states.push_back(ptr);


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

        // Render Frame
        renderFrame();

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
            states.at(currentState)->handleEvent(event);
            break;
        }
    }
}

// Update Game Logic
void Game::updateLogic(sf::Time const & frameDuration)
{
    states.at(currentState)->updateLogic(frameDuration);
}


// Render Frame
void Game::renderFrame()
{
    states.at(currentState)->renderFrame();
}

void Game::getNextState()
{
    currentState = states.at(currentState)->getNextState();
    if (currentState == MENU_STATE)
    {
        delete states.at(GAME_STATE);
        State* ptr = new GameState{window, currentStatePtr, music};
        states.at(GAME_STATE) = ptr;
    }
}