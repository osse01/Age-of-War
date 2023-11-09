#include "MenuState.h"

#include <iostream>
#include <cmath>

MenuState::MenuState(sf::RenderWindow* screen)
: image{new sf::Image {}}, texture{new sf::Texture {}}, sprite{new sf::Sprite {}},
  textFont{new sf::Font}, gameTitle{new sf::Text {}}, instructionText{new sf::Text {}},
  scale{1.0f}, t{0.0f}, fontFile{"coolFont.ttf"}, backroundFile{"backround.jpeg"}
  , window{screen}
//  -------------------------------------------------------
//  MenuState constructor. Loads in the Font Used for Text and Backround Image, the Name of the Files
//  are Saved in the fontFile and backroundFile Variables.
//  -------------------------------------------------------
{
    nextState = MENU_STATE;

    if(image->loadFromFile(backroundFile))
    {
    texture->loadFromImage(*image);
    sprite->setTexture(*texture);
    
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find backround image. Error in MenuState::MenuState().");
    }

    if(textFont->loadFromFile(fontFile))
    {
        gameTitle->setFont(*textFont);
        gameTitle->setString("AGE OF WAR");
        gameTitle->setCharacterSize(50);

        instructionText->setFont(*textFont);
        instructionText->setString("PRESS ANY KEY TO START");
        instructionText->setCharacterSize(20);
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find font .ttf file. Error in MenuState::MenuState().");
    }
}

void MenuState::handleEvent(sf::Event event)
//  ---------------------------------------------
//  Handle Event, For Now We Can Only Start Game.
//  ---------------------------------------------
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        startAnimation();
        nextState = GAME_STATE;

        break;
    
    default:
        break;
    }
}

int MenuState::getNextState()
//  ---------------------------------------------
//  Returns Wich State is The Next State.
//  ---------------------------------------------
{
    return  nextState;
}

void MenuState::updateLogic(sf::Time const & frameDuration)
//  ---------------------------------------------
//  Function to Handle User Input. User Input Triggers
//  an Event.
//  ---------------------------------------------
{}

void MenuState::startAnimation()
//  ---------------------------------------------
//  This Fuction Rescales the Backround Such That it
//  Looks like an animation.
//  ---------------------------------------------
{
    double  step{1};
    double  delay{0.5};

    sf::Vector2f zoomFactor(0.7f, 0.5f);

    
    while (step > 0)
    {
    window->clear(sf::Color(255, 255, 255));

    step = step - 0.0003;
    scale = std::pow(step, 2);

    sprite->setScale(zoomFactor);

    gameTitle->setOrigin(gameTitle->getLocalBounds().width / 2, gameTitle->getLocalBounds().height / 2);
    gameTitle->setPosition(320, 80);
    gameTitle->setFillColor(sf::Color::Black); 
    gameTitle->setCharacterSize(50*scale);

    instructionText->setOrigin(instructionText->getLocalBounds().width / 2, instructionText->getLocalBounds().height / 2);
    instructionText->setPosition(320, 160);
    instructionText->setFillColor(sf::Color::Black); 
    instructionText->setCharacterSize(20*scale);


    window->draw(*sprite);
    window->draw(*gameTitle);
    window->draw(*instructionText);
    window->display();

    sf::sleep(sf::milliseconds(delay)); 
    }

    window->clear(sf::Color(255, 255, 255));

    sprite->setScale(zoomFactor);

    window->draw(*sprite);
    window->display();
}


void MenuState::renderFrame(sf::RenderWindow& window)
//  ---------------------------------------------
//  Funcion Explaination
//  ---------------------------------------------
{
    window.clear(sf::Color(255, 255, 255));

    t = t + 0.0003;
    scale = 1.0 + 0.1 * std::cos(t * M_PI * 2);

    sf::Vector2f zoomFactor(0.7f, 0.5f);

    sprite->setScale(zoomFactor);

    gameTitle->setOrigin(gameTitle->getLocalBounds().width / 2, gameTitle->getLocalBounds().height / 2);
    gameTitle->setPosition(320, 80);
    gameTitle->setFillColor(sf::Color::Black); 
    gameTitle->setCharacterSize(50*scale);

    instructionText->setOrigin(instructionText->getLocalBounds().width / 2, instructionText->getLocalBounds().height / 2);
    instructionText->setPosition(320, 160);
    instructionText->setFillColor(sf::Color::Black); 

    window.draw(*sprite);
    window.draw(*gameTitle);
    window.draw(*instructionText);
}

