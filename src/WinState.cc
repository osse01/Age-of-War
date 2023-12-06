#include "../include/WinState.h"

WinState::WinState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap, std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration, sf::Texture& lastFrame)
: State(screen, dataMap, sound, frameDuration), nextState{WIN_STATE},
    textFont     {}, winText {}, 
    greyOut      {}, gamestateFrameTexture{lastFrame}, gamestateFrameSprite{}, gui { WIN_STATE, screen, dataMap }
{
    if(textFont.loadFromFile(dataMap.files["TitleFont"]))
    {
        winText.setFont          (textFont);
        winText.setString        ("You Win!");
        winText.setCharacterSize (50);
        winText.setOrigin        (winText.getLocalBounds().width / 2, winText.getLocalBounds().height / 2);
        winText.setPosition      (window->getSize().x / 2, window->getSize().y / 3);
        winText.setFillColor     (sf::Color::Black); 
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

WinState::~WinState()
{
    
}

void WinState::handleEvent(sf::Event event)
{
   switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
    {
        sf::Event::MouseButtonEvent mouse { event.mouseButton };
        if (mouse.button == sf::Mouse::Button::Left)
        {
            switch (gui.buttonClicked(WIN_STATE, mouse.x, mouse.y))
            {
                case 1:
                    nextState = MENU_STATE;
                    break;
                case 2:
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
void WinState::updateLogic()
{
    gui.updateLogic(window, WIN_STATE);
}

void WinState::renderFrame()
{
    window->clear(sf::Color(255, 0, 0));

    window->draw(gamestateFrameSprite);
    window->draw(greyOut);
    window->draw(winText);    
    gui.draw(WIN_STATE, window, 0);
}

int WinState::getNextState()
{
    return nextState;
}

void WinState::resetState()
{
    nextState = WIN_STATE;
}