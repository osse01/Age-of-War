#include "PauseState.h"

#include <iostream>
#include <cmath>

PauseState::PauseState(sf::RenderWindow* screen, int* curr, sf::Music* sound)
:   currentState { curr }, fontFile { "coolFont.ttf" }, window { screen },
    textFont     { new sf::Font{} }, pausedText { new sf::Text {} }, 
    greyOut      { new sf::RectangleShape{} }, music { sound }
  
//  -------------------------------------------------------
//  PauseState constructor. Loads in the Font Used for Text and Backround Image, the Name of the Files
//  are Saved in the fontFile and backroundFile Variables.
//
//  For Now File Names are Hardcoded Values. This must Change!!!
//  -------------------------------------------------------
{
    if(textFont->loadFromFile(fontFile))
    {
        pausedText->setFont          (*textFont);
        pausedText->setString        ("PAUSED");
        pausedText->setCharacterSize (50);
        pausedText->setOrigin        (pausedText->getLocalBounds().width / 2, pausedText->getLocalBounds().height / 2);
        pausedText->setPosition      (window->getSize().x / 2, window->getSize().y / 3);
        pausedText->setFillColor     (sf::Color::Black); 
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find font .ttf file. Error in PauseState::PauseState().");
    }
    greyOut->setSize(static_cast<sf::Vector2f>(window->getSize()));
    greyOut->setFillColor(sf::Color(115, 90, 100, 2));
}

void PauseState::handleEvent(sf::Event event)
//  ---------------------------------------------
//  Handle Event, For Now We Can Only Start Game.
//  ---------------------------------------------
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        music->play();
        startAnimation();
        *currentState = GAME_STATE;      
        break;
    default:
        break;
    }
}

int PauseState::getNextState()
//  ---------------------------------------------
//  Returns Wich State is The Next State.
//  ---------------------------------------------
{
    return  *currentState;
}

void PauseState::updateLogic(sf::Time const & frameDuration)
//  ---------------------------------------------
//  Function to Handle User Input. User Input Triggers
//  an Event.
//  ---------------------------------------------
{}

void PauseState::startAnimation()
//  ---------------------------------------------
//  This Fuction Rescales the Backround Such That it
//  Looks like an animation.
//  ---------------------------------------------
{}

void PauseState::renderFrame()
//  ---------------------------------------------
//  Funcion Explaination
//  ---------------------------------------------
{
    window->draw(*greyOut);

    window->draw(*pausedText);
}

