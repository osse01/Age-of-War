#include "Game.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"

#include <memory>
#include <iostream>


Game::Game(std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight)
:   window { new sf::RenderWindow { sf::VideoMode { gameWidth, gameHeight }, GAME_TITLE } },
    event {}, running { true }, clock {}, frameDuration {}, frameDurationPtr { &frameDuration }, currentStage {}, states {}, currentState { MENU_STATE }, 
    currentStatePtr { &currentState }, music {new sf::Music }, nextState {}
{
    // Open Audio File
    std::string file{"assets/Age-of-War-Theme-Song.ogg"};
    if (!music->openFromFile(file))
    {
        std::cout << "  >> Error: Could Not Find Audio File. Error in GameState::GameState()." << std::endl;
    }
    music->setVolume(50);
    music->setLoop(true);

    //Place Possible Game States in States Vector
    State* ptr = new MenuState{window, currentStatePtr, music, frameDurationPtr};
    states.push_back(ptr);
    
    ptr = new GameState{window, currentStatePtr, music, frameDurationPtr};
    states.push_back(ptr);

    ptr = new PauseState{window, currentStatePtr, music, frameDurationPtr};
    states.push_back(ptr);

}

Game::~Game()
{
    delete states.at(MENU_STATE);
    delete states.at(GAME_STATE);
    delete states.at(PAUSE_STATE);

    states.at(MENU_STATE) = nullptr;
    states.at(GAME_STATE) = nullptr;
    states.at(PAUSE_STATE) = nullptr;
   
    delete music;
    //music = nullptr;
    //window->close();
    delete window;
    //window = nullptr;
    currentStatePtr     = nullptr;
    frameDurationPtr    = nullptr;
}


// Functions //

// Start Game
void Game::startGame ()
{

    // Main Game Loop, One Iteration is a Frame
    while ( running )
    {
        frameDuration = clock.restart();

        // Handle Events
        handleEvents();

        // Update Logic
        updateLogic();

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
void Game::updateLogic()
{
    states.at(currentState)->updateLogic();
}


// Render Frame
void Game::renderFrame()
{
    states.at(currentState)->renderFrame();
}

void Game::getNextState()
{
    
    /*if (currentState == MENU_STATE)
    {
        delete states.at(GAME_STATE);
        State* ptr = new GameState{window, currentStatePtr, music, frameDurationPtr};
        states.at(GAME_STATE) = ptr;
    }*/
    if (currentState == MENU_STATE)
    {
        std::cout << "w" << std::endl;
        currentState = states.at(currentState)->getNextState();
        std::cout << currentState << std::endl;
        if (*currentStatePtr == GAME_STATE)
        {
            std::cout << "inne" << std::endl;
            delete states.at(GAME_STATE);
            State* ptr = new GameState{window, currentStatePtr, music, frameDurationPtr};
            states.at(GAME_STATE) = ptr;
        }
        return;
    }
    else if (currentState == GAME_STATE)
    {
        currentState = states.at(currentState)->getNextState();
        //std::cout << currentState << std::endl;
        if (*currentStatePtr == MENU_STATE)
        {
            std::cout << "inne nu" << std::endl;
            delete states.at(MENU_STATE);
            State* ptr = new MenuState{window, currentStatePtr, music, frameDurationPtr};
            states.at(MENU_STATE) = ptr;
        }
        return;
    }
    else if (currentState == PAUSE_STATE)
    {
        currentState = states.at(currentState)->getNextState();
        std::cout << currentState << std::endl;
        if (*currentStatePtr == GAME_STATE)
        {
            std::cout << "inne tre" << std::endl;
            delete states.at(PAUSE_STATE);
            State* ptr = new PauseState{window, currentStatePtr, music, frameDurationPtr};
            states.at(PAUSE_STATE) = ptr;
        }
        return;
    }

}