#include "../include/PauseState.h"

#include <iostream>
#include <cmath>

PauseState::PauseState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap, std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration, sf::Texture& lastFrame)
:   State(screen, dataMap, sound, frameDuration), nextState{PAUSE_STATE},
    textFont {}, pausedText {}, greyOut {}, gamestateFrameTexture{lastFrame}, gamestateFrameSprite{}, gui { PAUSE_STATE, screen, dataMap }
{
    music->pause();

    // Set Appearance and Position for Pause Text
    if(textFont.loadFromFile(dataMap.files["TitleFont"]))
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

    //  Load Last GameState Frame
    gamestateFrameSprite.setTexture(gamestateFrameTexture);
}

PauseState::~PauseState()
{
    music->play();
}

void PauseState::handleEvent(sf::Event event)
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
                // Change to Game State
                case 1:
                    nextState = GAME_STATE;
                    break;
                case 2:
                    break;
                // Change to Menu State
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

// Return next State
int PauseState::getNextState()
{
    return  nextState;
}

// Handle User Input that Triggers an Event
void PauseState::updateLogic()
{
    gui.updateLogic(window, PAUSE_STATE);
}

// Draw Next Frame
void PauseState::renderFrame()
{
    window->clear(sf::Color(255, 255, 255));
    window->draw(gamestateFrameSprite);
    window->draw(greyOut);
    window->draw(pausedText);

    gui.draw(PAUSE_STATE, window, 0);
}

// Reset nextState Variable to Pause State
void PauseState::resetState()
{
    nextState = PAUSE_STATE;
}