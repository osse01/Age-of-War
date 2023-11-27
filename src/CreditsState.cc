#include "../include/CreditsState.h"

CreditsState::CreditsState(std::shared_ptr<sf::RenderWindow> window,
     std::shared_ptr<sf::Music> gameMusic, std::shared_ptr<sf::Time> frameDuration)
//  ---------------------------------------------
:   State(window, gameMusic, frameDuration), nextState{ CREDITS_STATE }, elapsedTime{ 0 },
    nameList{}, font{}, backgroundTexture{}, backgroundSprite{}, canvas{}
{
    //  Load background image
    if(!backgroundTexture.loadFromFile("assets/background.jpeg"))
    {
        throw std::logic_error("    >> Error: Could Not Find credits image."
         "Error in CreditsState::CreditsState().");
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(window->getSize().x /backgroundSprite.getGlobalBounds().width,
    window->getSize().y /backgroundSprite.getGlobalBounds().height);
    
    //  Load font
    if(!font.loadFromFile("assets/royalFont.ttf"))
    {
        throw std::logic_error("    >> Error: Could Not Find credits image."
         "Error in CreditsState::CreditsState().");
    }
    
    //  List of contributors
    std::list<std::string> stringList {"Oskar Bollner", "Logan Eriksson", 
    "Adam Hallberg", "Oscar Jemsson", "Johanna Nilsson", "Filip Ripstrand"};
    for ( auto &name : stringList)
    {
        nameList.push_back(sf::Text{name, font, 30});
    }

    //  Init canvas
    canvas.create(window->getSize().x, window->getSize().y*20);
}

CreditsState::~CreditsState()
//  ---------------------------------------------
{}

void CreditsState::setupCanvas()
//  ---------------------------------------------
{
    
}

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
    elapsedTime = 0;
    nextState   = CREDITS_STATE;
}

void CreditsState::handleEvent(sf::Event event)
//  ---------------------------------------------
{
    switch(event.type)
        {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::F10:
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
    elapsedTime += frameDuration->asSeconds();
    window->clear(sf::Color(5, 0, 43));

    backgroundSprite.setPosition(backgroundSprite.getGlobalBounds().left,
        backgroundSprite.getGlobalBounds().top - 50 * frameDuration->asSeconds()); // Make slower later


    window->draw(backgroundSprite);
}
