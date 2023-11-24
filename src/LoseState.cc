#include "../include/LoseState.h"

LoseState::LoseState(std::shared_ptr<sf::RenderWindow> screen, std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
: State(screen, sound, frameDuration), nextState{LOSE_STATE}, fontFile { "assets/coolFont.ttf" },
    textFont     { new sf::Font{} }, loseText { new sf::Text {} }, 
    greyOut      { new sf::RectangleShape{} }
{
    if(textFont->loadFromFile(fontFile))
    {
        loseText->setFont          (*textFont);
        loseText->setString        ("You Lose!");
        loseText->setCharacterSize (50);
        loseText->setOrigin        (loseText->getLocalBounds().width / 2, loseText->getLocalBounds().height / 2);
        loseText->setPosition      (window->getSize().x / 2, window->getSize().y / 3);
        loseText->setFillColor     (sf::Color::Black); 
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find font .ttf file. Error in PauseState::PauseState().");
    }
    greyOut->setSize(static_cast<sf::Vector2f>(window->getSize()));
    greyOut->setFillColor(sf::Color(115, 90, 100, 2));

}

LoseState::~LoseState()
{
    
}

void LoseState::handleEvent(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        nextState = MENU_STATE;      
        break;
    default:
        break;
    }

}

void LoseState::updateLogic()
{

}

void LoseState::renderFrame()
{
    window->draw(*greyOut);

    window->draw(*loseText);
}

int LoseState::getNextState()
{
    return nextState;
}

void LoseState::resetState()
{
    nextState = LOSE_STATE;
}