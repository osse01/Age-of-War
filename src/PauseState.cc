#include "../include/PauseState.h"

#include <iostream>
#include <cmath>

PauseState::PauseState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap, std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
:   State(screen, dataMap, sound, frameDuration), nextstate{PAUSE_STATE},
    textFont     { new sf::Font{} }, pausedText { new sf::Text {} }, 
    greyOut      { new sf::RectangleShape{} }
  
//  -------------------------------------------------------
//  PauseState constructor. Loads in the Font Used for Text and Backround Image, the Name of the Files
//  are Saved in the fontFile and backroundFile Variables.
//
//  For Now File Names are Hardcoded Values. This must Change!!!
//  -------------------------------------------------------
{
    if(textFont->loadFromFile(dataMap.files["GameFont"]))
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

PauseState::~PauseState()
{
    delete textFont;
    delete pausedText;
    delete greyOut;
    window = nullptr;
    frameDuration = nullptr;
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
        nextstate = GAME_STATE;      
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
    return  nextstate;
}



void PauseState::updateLogic()
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

void PauseState::resetState()
{
    nextstate = PAUSE_STATE;
}