#include "../include/CreditsState.h"

CreditsState::CreditsState(std::shared_ptr<sf::RenderWindow> window,
     std::shared_ptr<sf::Music> gameMusic, std::shared_ptr<sf::Time> frameDuration)
//  ---------------------------------------------
:   State(window, gameMusic, frameDuration), nextState{ CREDITS_STATE }, 
    backgroundTexture{}, backgroundSprite{}
{
    if(backgroundTexture.loadFromFile("assets/background.jpeg"))
    {
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(window->getSize().x /backgroundSprite.getGlobalBounds().width,
            window->getSize().y /backgroundSprite.getGlobalBounds().height);
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find credits image."
         "Error in CreditsState::CreditsState().");
    }
}

CreditsState::~CreditsState()
//  ---------------------------------------------
{}

int CreditsState::getNextState()
//  ---------------------------------------------
{
    return nextState;
}

void CreditsState::updateLogic()
//  ---------------------------------------------
{}

void CreditsState::resetState()
//  ---------------------------------------------
{
    nextState = CREDITS_STATE;
}

void CreditsState::handleEvent(sf::Event event)
//  ---------------------------------------------
{
    switch(event.type)
        {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    nextState = MENU_STATE;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
        }
}

void CreditsState::renderFrame()
//  ---------------------------------------------
{
    window->clear(sf::Color(255, 255, 255));
    window->draw(backgroundSprite);
}
