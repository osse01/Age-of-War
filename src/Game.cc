#include "../include/Game.h"
#include "../include/MenuState.h"
#include "../include/GameState.h"
#include "../include/PauseState.h"

#include <utility>
#include <iostream>


Game::Game(std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight)
:   window { std::make_shared<sf::RenderWindow> ( sf::VideoMode { gameWidth, gameHeight }, GAME_TITLE) },
    event {}, clock {}, frameDuration {}, frameDurationPtr { std::make_shared<sf::Time> ( frameDuration )}, states {}, currentState { MENU_STATE },
    music { std::make_shared<sf::Music> () }, nextState {MENU_STATE}
{
    window->create(sf::VideoMode::getDesktopMode(), "My window", sf::Style::Fullscreen);
    // Open Audio File
    std::string file{"assets/Age-of-War-Theme-Song.ogg"};
    if (!music->openFromFile(file))
    {
        std::cout << "  >> Error: Could Not Find Audio File. Error in GameState::GameState()." << std::endl;
    }
    music->setVolume(50);
    music->setLoop(true);
    
    // Place Possible Game States in States Vector
    std::unique_ptr<State> ptr = std::make_unique<MenuState>(window, music, frameDurationPtr);
    states.push(std::move(ptr));

}

Game::~Game()
{}


// Functions //

// Start Game
void Game::startGame ()
{

    // Main Game Loop, One Iteration is a Frame
    while ( window->isOpen() )
    {
        *frameDurationPtr = clock.restart();

        // Handle Events
        handleEvents();

        // Update Logic
        updateLogic();

        // Update Current State
        getNextState();

        // Render Frame
        renderFrame();

        // Display Frame
        window->display();

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
            Other Events Are Handled by the Current Game State
        */
        {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Backspace)
            {
                window->close();    
                break;
            }
            // Let Current Game State Handle Event
            states.top()->handleEvent(event);
            break;
            
        default:
            // Let Current Game State Handle Event
            states.top()->handleEvent(event);
            break;
        }
    }
}

// Update Game Logic
void Game::updateLogic()
{
    states.top()->updateLogic();
}


// Render Frame
void Game::renderFrame()
{
    states.top()->renderFrame();
}

void Game::getNextState()
{
    
    nextState = states.top()->getNextState();

    if ( currentState != nextState)
    {
        std::unique_ptr<State> ptr {};
        switch (nextState)
        {
            case MENU_STATE:
                states.pop();

                break;
            case PAUSE_STATE:
                states.top()->resetState();
                ptr = std::make_unique<PauseState>(window, music, frameDurationPtr);            
                states.push(std::move(ptr));
                break;
            case GAME_STATE:
                if(currentState == PAUSE_STATE)
                {
                    states.pop();
                    
                }
                else if(currentState == MENU_STATE) 
                {
                    states.top()->resetState();
                    ptr = std::make_unique<GameState>(window, music, frameDurationPtr);
                    states.push(std::move(ptr));
                }

                break;
        }
        currentState = nextState;

    }

}