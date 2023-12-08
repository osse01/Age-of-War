#include "../include/MenuState.h"

#include <iostream>
#include <cmath>

MenuState::MenuState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap, std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
:   State(screen, dataMap, sound, frameDuration), scale{1.0f}, t{0.0f}, nextState{MENU_STATE},
    texture{}, sprite{}, textFont{}, gameTitle{}, instructionText{},
    zoomFactor{sf::Vector2f(0.9f, 0.6f)}, gui { MENU_STATE, screen, dataMap }
    //  -------------------------------------------------------
    //  Load in the Font Used for Text and Background Image
    //  The Name of the Files are Saved in the fontFile and backgroundFile Variables
    //  -------------------------------------------------------
{
    // Load Background Image
    if(texture.loadFromFile(dataMap.files["Background"]))
    {
        sprite.setTexture(texture);
        //sprite.setScale(zoomFactor);
        sprite.setScale(window->getSize().x /sprite.getGlobalBounds().width, window->getSize().y /sprite.getGlobalBounds().height);
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find background image. Error in MenuState::MenuState().");
    }

    // Set Game Title Appearance and Position
    if(textFont.loadFromFile(dataMap.files["TitleFont"]))
    {
        gameTitle.setFont(textFont);
        gameTitle.setString("AGE OF WAR");
        gameTitle.setCharacterSize(75);
        gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2, gameTitle.getLocalBounds().height / 2);
        gameTitle.setPosition(window->getSize().x / 2, window->getSize().y / 3);
        gameTitle.setFillColor(sf::Color::Black); 
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find font .ttf file. Error in MenuState::MenuState().");
    }
}

MenuState::~MenuState()
{}

void MenuState::handleEvent(sf::Event event)
//  ---------------------------------------------
{
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            sf::Event::MouseButtonEvent mouse { event.mouseButton };
            if (mouse.button == sf::Mouse::Button::Left)
            {
                switch (gui.buttonClicked(MENU_STATE, mouse.x, mouse.y))
                {
                    // Change to Game State
                    case 1:
                        nextState = GAME_STATE;
                        startAnimation();
                        break;
                    // Change to Options State
                    case 2:
                        break;
                    // Change to Credits State
                    case 3:
                        nextState = CREDITS_STATE;
                        break;
                    // Quit Game
                    case 4:
                        window->close();
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

// Return Next State
int MenuState::getNextState()
{
    return  nextState;
}

// Reset nextState Variable to Menu State
void MenuState::resetState()
{
    nextState = MENU_STATE;
}

// Handle User Input that Triggers an Event
void MenuState::updateLogic()
{
        gui.updateLogic(window, MENU_STATE);
}

//Rescale Background such that it Looks like an Animation when Entering Game
void MenuState::startAnimation()
{
    double  step{1};
    //// double  delay{0.5};
    double  stepBackground{1};
    //// float   backgroundScale{1};
    sf::Event event{};
    
    while (step > 0 && stepBackground >0)
    {
        window->clear(sf::Color(255, 255, 255));

        step -= 0.01;
        stepBackground -= 0.002;
        scale = std::pow(step, 2);
        // backgroundScale = std::pow(stepBackground, 2);


        gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2, gameTitle.getLocalBounds().height / 2);
        gameTitle.setScale(zoomFactor*scale);

        instructionText.setOrigin(instructionText.getLocalBounds().width / 2, instructionText.getLocalBounds().height / 2);
        instructionText.setScale(zoomFactor*scale);

        //if(sprite.getGlobalBounds().width >= window->getSize().x)
        //{
        //    sprite.setScale(zoomFactor*backgroundScale);    
        //}
        window->pollEvent(event);
        if(event.type == sf::Event::KeyPressed)
        {
            break;
        }
        while(window->pollEvent(event))
        {
        }
        window->draw(sprite);
        window->draw(gameTitle);
        window->draw(instructionText);
        window->display();
    }
}

// Render the Frame to Display
void MenuState::renderFrame()
{
    window->clear(sf::Color(255, 255, 255));

    t = t + 0.25*frameDuration->asSeconds();
    scale = 1.0 + 0.1 * std::cos(t * M_PI * 2);

    gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2, gameTitle.getLocalBounds().height / 2);
    gameTitle.setScale(zoomFactor*scale);

    instructionText.setScale(zoomFactor);

    window->draw(sprite);
    window->draw(gameTitle);
    window->draw(instructionText);

    gui.draw(MENU_STATE, window, 0);
}