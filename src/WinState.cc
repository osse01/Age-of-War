#include "../include/WinState.h"

WinState::WinState(std::shared_ptr<sf::RenderWindow> screen,
                   FileReader::Data& dataMap,
                   std::shared_ptr<sf::Music> music, 
                   std::map<std::string, std::shared_ptr<sf::Sound>> sound,
                   std::shared_ptr<sf::Time> frameDuration, 
                   sf::Texture& lastFrame)
: State(screen, dataMap, music, sound, frameDuration), nextState{WIN_STATE},
    textFont     {}, winText {}, 
    greyOut      {}, gamestateFrameTexture{lastFrame}, gamestateFrameSprite{}, gui { WIN_STATE, screen, dataMap }
{
    // Set Appearance and Position for Win Text
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
{}

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
                // Change State to Menu State when Pressing First Button
                case 1:
                    nextState = MENU_STATE;
                    sound["button"]->play();
                    break;
                // Quit Game when Pressing Second Button
                case 2:
                    sound["button"]->play();
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

// Handle User Input that Triggers an Event
void WinState::updateLogic()
{
    gui.updateLogic(window, WIN_STATE);
}

// Draw Win State
void WinState::renderFrame()
{
    window->clear(sf::Color(255, 0, 0));
    window->draw(gamestateFrameSprite);
    window->draw(greyOut);
    window->draw(winText);    
    gui.draw(WIN_STATE, window, 0);
}

// Return Next State
int WinState::getNextState()
{
    return nextState;
}

// Reset nextState Variable to Win State
void WinState::resetState()
{
    nextState = WIN_STATE;
}