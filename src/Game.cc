#include "../include/Game.h"
#include "../include/MenuState.h"
#include "../include/GameState.h"
#include "../include/PauseState.h"
#include "../include/WinState.h"
#include "../include/LoseState.h"
#include "../include/CreditsState.h"
#include "../include/OptionsState.h"


#include <utility>
#include <iostream>


Game::Game(std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight)
:   window { std::make_shared<sf::RenderWindow> ( sf::VideoMode { gameWidth, gameHeight }, GAME_TITLE) },
    event {}, clock {}, frameDurationPtr { std::make_shared<sf::Time> ()}, states {}, currentState { MENU_STATE },
    music { std::make_shared<sf::Music> () }, nextState {MENU_STATE}, cursor {}, lastFrame{}, cursorSprite {}, mouse{}, dataMap {}
{
    // Create Fullscreen Window
    window->create(sf::VideoMode::getDesktopMode(), "My window", sf::Style::Fullscreen);
    
    // Load required data
    FileReader reader {window};
    dataMap = reader.returnData("assets/Data.txt");

    // Open Audio File
    std::string file{dataMap.files["GameMusic"]};
    if (!music->openFromFile(file))
    {
        std::cout << "  >> Error: Could Not Find Audio File. Error in Game::Game()." << std::endl;
    }
    music->setVolume(dataMap.stats["GameMusic"]["volume"]);
    music->setLoop(true);
    
    // Place Possible Game States in States Vector
    std::unique_ptr<State> ptr = std::make_unique<MenuState>(window, dataMap, music, frameDurationPtr);
    states.push(std::move(ptr));

    // Create Custom Cursor
    if(!cursor.loadFromFile(dataMap.files["Cursor"]))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find cursor image. Error in Game::Game().");
    }
    cursorSprite.setTexture(cursor);
    cursorSprite.setScale(window->getSize().y / cursorSprite.getGlobalBounds().height / 20,
                          window->getSize().y / cursorSprite.getGlobalBounds().height / 20);


}

Game::~Game()
{}


// Functions //

// Start Game
void Game::startGame ()
{
    window->setMouseCursorVisible(false);
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
            // Let Current State Handle Event
            states.top()->handleEvent(event);
            break;
            
        default:
            // Let Current State Handle Event
            states.top()->handleEvent(event);
            break;
        }
    }
}

// Update Game Logic
void Game::updateLogic()
{
    // Set Custom Cursor Position to Mouse Position
    cursorSprite.setPosition(mouse.getPosition(*window).x, mouse.getPosition(*window).y);
    // Let Curent State Update Logic
    states.top()->updateLogic();
}


// Render Frame
void Game::renderFrame()
{
    // Let Curent State Render Frame
    states.top()->renderFrame();
    window->draw(cursorSprite);
}

void Game::getNextState()
{
    // Let Curent State get Next State
    nextState = states.top()->getNextState();

    if ( currentState != nextState)
    {
        std::unique_ptr<State> ptr {};
        switch (nextState)
        {
            // Remove all States Except Menu State
            case MENU_STATE:
                do
                {
                    states.pop();
                }
                while(states.size() > 1);
                break;

            // Remove Pause State or Create Game State
            case GAME_STATE:
                if(currentState == PAUSE_STATE)
                {
                    states.pop();
                }
                else if(currentState == MENU_STATE) 
                {
                    states.top()->resetState();
                    ptr = std::make_unique<GameState>(window, dataMap, music, frameDurationPtr);
                    states.push(std::move(ptr));
                }
                break;

            // Save Current Graphics and Create Pause State
            case PAUSE_STATE:
                states.top()->renderFrame();
                saveFrame();
                states.top()->resetState();
                ptr = std::make_unique<PauseState>(window, dataMap, music, frameDurationPtr, lastFrame);            
                states.push(std::move(ptr));
                break;

            // Create Win State
            case WIN_STATE:
                states.top()->renderFrame();
                saveFrame();
                states.top()->resetState();
                ptr = std::make_unique<WinState>(window, dataMap, music, frameDurationPtr, lastFrame);            
                states.push(std::move(ptr));
                break;

            // Create Lose State
            case LOSE_STATE:
                states.top()->renderFrame();
                saveFrame();
                states.top()->resetState();
                ptr = std::make_unique<LoseState>(window, dataMap, music, frameDurationPtr, lastFrame);            
                states.push(std::move(ptr));
                break;

            // Create Credits State
            case CREDITS_STATE:
                states.top()->resetState();
                ptr = std::make_unique<CreditsState>(window, dataMap, music, frameDurationPtr);            
                states.push(std::move(ptr));
                break;
            case OPTIONS_STATE:
                if(currentState == MENU_STATE) 
                {
                    states.top()->resetState();
                    ptr = std::make_unique<OptionsState>(window, dataMap, music, frameDurationPtr);
                    states.push(std::move(ptr));
                }
                break;
            default:
                break;
        }
        currentState = nextState;
    }

}

void Game::saveFrame()
//  ---------------------------------------------
{
    lastFrame.loadFromImage(window->capture());
}