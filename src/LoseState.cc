#include "../include/LoseState.h"

LoseState::LoseState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap, std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration, sf::Texture lastFrame)
: State(screen, dataMap, sound, frameDuration), nextState{LOSE_STATE},
    textFont     {}, loseText {}, 
    greyOut      {}, gamestateFrameTexture{lastFrame}, gamestateFrameSprite{}, gui { LOSE_STATE, screen, dataMap }
{
    if(textFont.loadFromFile(dataMap.files["TitleFont"]))
    {
        loseText.setFont          (textFont);
        loseText.setString        ("You Lose!");
        loseText.setCharacterSize (50);
        loseText.setOrigin        (loseText.getLocalBounds().width / 2, loseText.getLocalBounds().height / 2);
        loseText.setPosition      (window->getSize().x / 2, window->getSize().y / 3);
        loseText.setFillColor     (sf::Color::Black); 
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

LoseState::~LoseState()
{
}

void LoseState::handleEvent(sf::Event event)
{
   switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
    {
        sf::Event::MouseButtonEvent mouse { event.mouseButton };
        if (mouse.button == sf::Mouse::Button::Left)
        {
            switch (gui.buttonClicked(LOSE_STATE, mouse.x, mouse.y))
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

void LoseState::updateLogic()
{
    gui.updateLogic(window, LOSE_STATE);
}

void LoseState::renderFrame()
{
    window->clear(sf::Color(255, 0, 0));

    window->draw(gamestateFrameSprite);
    window->draw(greyOut);
    window->draw(loseText);
    gui.draw(LOSE_STATE, window, 0);
}

int LoseState::getNextState()
{
    return nextState;
}

void LoseState::resetState()
{
    nextState = LOSE_STATE;
}