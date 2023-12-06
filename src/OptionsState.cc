#include "../include/OptionsState.h"

OptionsState::OptionsState(std::shared_ptr<sf::RenderWindow> window, FileReader::Data& data, std::shared_ptr<sf::Music> music, std::shared_ptr<sf::Time> frameDuration)
: State{window, data, music, frameDuration}, gui{OPTIONS_STATE, window, data}, data{data},
  musicVolume {music->getVolume()}, soundEnabled { true }, musicEnabled { music->getVolume() > 0 },
  buttonPressed { false }, buttonNumber { 0 }
{}

void OptionsState::handleEvent(sf::Event event)
// A function to handle Option events 
// such as Sound Volume, Music Volume, and Sound Enabled
{
    sf::Event::MouseButtonEvent mouse = event.mouseButton;
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            if (mouse.button == sf::Mouse::Button::Left)
            {
                buttonNumber = gui.buttonClicked(OPTIONS_STATE, mouse.x, mouse.y);
                buttonPressed = true;
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            buttonPressed = false;
            data.stats["GameMusic"]["volume"] = musicVolume;
            data.stats["GameSound"]["volume"] = soundVolume;
            std::cout << "GameSound: " << data.stats["GameSound"]["volume"] << std::endl;
            std::cout << "GameMusic: " << data.stats["GameMusic"]["volume"] << std::endl;
            break;
        }
        default:
        break;
    }
    if (buttonPressed)
    {
        switch(buttonNumber)
        {
            case 1:
            musicVolume = gui.buttonPosition(1, mouse.x, mouse.y);
            break;

            case 4:
            soundVolume = gui.buttonPosition(4, mouse.x, mouse.y);
            break;

            case 2:
            musicEnabled = (musicEnabled) ? false: true;
            break;

            case 5:
             soundEnabled = (soundEnabled) ? false: true;
            break;
            case 7:
            nextState = MENU_STATE;
            break;

            default:
            break;
        }
    }
    music->setVolume(musicEnabled ? musicVolume : 0);
    //sound->setVolume(soundEnabled? soundVolume : 0);

}
void OptionsState::renderFrame()
// A function to render the Options State
{
    window->clear();
    gui.draw(OPTIONS_STATE, window);
}

int OptionsState::getNextState()
// A function to return the next state
{
    return nextState;
}

void OptionsState::updateLogic()
// A function to update the Options State
{
    gui.updateLogic(window, OPTIONS_STATE);
}

void OptionsState::resetState()
//  ---------------------------------------------
//  Sets Next State to PAUSED_STATE.
//  ---------------------------------------------
{
    nextState = OPTIONS_STATE;
}