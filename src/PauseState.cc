#include "../include/PauseState.h"

#include <iostream>
#include <cmath>

PauseState::PauseState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap, std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
:   State(screen, dataMap, sound, frameDuration), nextState{PAUSE_STATE},
    textFont {}, pausedText {}, greyOut {}, gui { PAUSE_STATE, screen, dataMap }
  
//  -------------------------------------------------------
//  PauseState constructor. Setup for pausedText and grayOut.
//  -------------------------------------------------------
{
    if(textFont.loadFromFile(dataMap.files["GameFont"]))
    {
        pausedText.setFont          (textFont);
        pausedText.setString        ("PAUSED");
        pausedText.setCharacterSize (50);
        pausedText.setOrigin        (pausedText.getLocalBounds().width / 2, pausedText.getLocalBounds().height / 2);
        pausedText.setPosition      (window->getSize().x / 2, window->getSize().y / 3);
        pausedText.setFillColor     (sf::Color::Black); 
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find font .ttf file. Error in PauseState::PauseState().");
    }
    greyOut.setSize(static_cast<sf::Vector2f>(window->getSize()));
    greyOut.setFillColor(sf::Color(115, 90, 100, 2));
}

PauseState::~PauseState()
//  ---------------------------------------------
//  PausedState Destructor.
//  ---------------------------------------------
{
    window = nullptr;
    frameDuration = nullptr;
}

void PauseState::handleEvent(sf::Event event)
//  ---------------------------------------------
//  Handle Event, When any Key is Pressed the Game
//  is Resumed.
//  ---------------------------------------------
{
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
    {
        sf::Event::MouseButtonEvent mouse { event.mouseButton };
        if (mouse.button == sf::Mouse::Button::Left)
        {
            switch (gui.buttonClicked(PAUSE_STATE, mouse.x, mouse.y))
            {
                case 1:
                    nextState = GAME_STATE;
                    music->play();      
                    break;
                case 2:
                    break;
                case 3:
                    nextState = MENU_STATE;
                    break;
                default:
                    break;
            }
        }
        break;
    }

    default:
        break;
    }
}

int PauseState::getNextState()
//  ---------------------------------------------
//  Returns Wich State is The Next State.
//  ---------------------------------------------
{
    return  nextState;
}

void PauseState::updateLogic()
//  ---------------------------------------------
//  Function to Handle User Input. User Input Triggers
//  an Event.
//  ---------------------------------------------
{
    gui.updateLogic(window, PAUSE_STATE);
}

void PauseState::renderFrame()
//  ---------------------------------------------
//  Draws next Frame.
//  ---------------------------------------------
{
    window->draw(greyOut);
    window->draw(pausedText);

    gui.draw(PAUSE_STATE, window, 0);
}

void PauseState::resetState()
//  ---------------------------------------------
//  Sets Next State to PAUSED_STATE.
//  ---------------------------------------------
{
    nextState = PAUSE_STATE;
}