#include "../include/WinState.h"

WinState::WinState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap, std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration, sf::Texture lastFrame)
: State(screen, dataMap, sound, frameDuration), nextState{WIN_STATE},
    textFont     { new sf::Font{} }, winText { new sf::Text {} }, 
    greyOut      { new sf::RectangleShape{} }, gamestateFrameTexture{lastFrame}, gamestateFrameSprite{}
{
    if(textFont->loadFromFile(dataMap.files["TitleFont"]))
    {
        winText->setFont          (*textFont);
        winText->setString        ("You Win!");
        winText->setCharacterSize (50);
        winText->setOrigin        (winText->getLocalBounds().width / 2, winText->getLocalBounds().height / 2);
        winText->setPosition      (window->getSize().x / 2, window->getSize().y / 3);
        winText->setFillColor     (sf::Color::Black); 
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find font .ttf file. Error in PauseState::PauseState().");
    }
    greyOut->setSize(static_cast<sf::Vector2f>(window->getSize()));
    greyOut->setFillColor(sf::Color(115, 90, 100, 2));

    //  Load Last GameState Frame
    gamestateFrameSprite.setTexture(gamestateFrameTexture);
}

WinState::~WinState()
{
    
}

void WinState::handleEvent(sf::Event event)
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

void WinState::updateLogic()
{

}

void WinState::renderFrame()
{
    window->clear(sf::Color(255, 0, 0));

    window->draw(gamestateFrameSprite);
    window->draw(*greyOut);
    window->draw(*winText);
}

int WinState::getNextState()
{
    return nextState;
}

void WinState::resetState()
{
    nextState = WIN_STATE;
}