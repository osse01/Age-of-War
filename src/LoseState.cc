#include "../include/LoseState.h"

LoseState::LoseState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap, std::shared_ptr<sf::Music> music, 
                     std::map<std::string, std::shared_ptr<sf::Sound>> sound, std::shared_ptr<sf::Time> frameDuration, sf::Texture& lastFrame)
: State(screen, dataMap, music, sound, frameDuration), nextState{LOSE_STATE},
    textFont     {}, loseText {}, 
    greyOut      {}, gamestateFrameTexture{lastFrame}, gamestateFrameSprite{}, gui { LOSE_STATE, screen, dataMap }
{
    music->pause();
    // Set Appearance and Position for Lose Text
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
{}

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
                // Change State to Menu State when Pressing First Button
                case 1:
                    nextState = MENU_STATE;
                    sound["button"]->play();
                    break;
                // Quit Game when Pressing Second Button
                case 2:
                    window->close();
                    sound["button"]->play();
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

// Handle User Input that Triggers an Event
void LoseState::updateLogic()
{
    gui.updateLogic(window, LOSE_STATE);
}

// Draw Lose State
void LoseState::renderFrame()
{
    window->clear(sf::Color(255, 0, 0));

    window->draw(gamestateFrameSprite);
    window->draw(greyOut);
    window->draw(loseText);
    gui.draw(LOSE_STATE, window, 0);
}

// Return Next State
int LoseState::getNextState()
{
    return nextState;
}

// Reset nextState Variable to Lose State
void LoseState::resetState()
{
    nextState = LOSE_STATE;
}