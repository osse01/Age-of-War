#include "../include/OptionsState.h"

OptionsState::OptionsState(std::shared_ptr<sf::RenderWindow> window, FileReader::Data& data, std::shared_ptr<sf::Music> music, std::shared_ptr<sf::Time> frameDuration)
: State{window, data, music, frameDuration}, 
  gui{OPTIONS_STATE, window, data}, data { data }, nextState {OPTIONS_STATE},
  soundVolume {data.stats["GameSound"]["volume"]}, musicVolume {data.stats["GameMusic"]["volume"]}, soundEnabled { true }, musicEnabled { music->getVolume() > 0 },
  buttonPressed { false }, buttonNumber { 0 }
{
    music->play();
}

OptionsState::~OptionsState()
{
    music->stop();
}
void OptionsState::handleEvent(sf::Event event)
// A function to handle Option events 
// such as Sound Volume, Music Volume, and Sound Enabled
{
    sf::Event::MouseButtonEvent mouse = event.mouseButton;
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            buttonNumber = gui.buttonClicked(OPTIONS_STATE, mouse.x, mouse.y);
            break;
        }
        case sf::Event::MouseButtonReleased:
        {

            break;
        }
        default:
        break;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        float xpos = sf::Mouse::getPosition().x;
        
        switch(buttonNumber)
        {
            case 1:
            musicVolume = gui.buttonPosition(1, xpos);
            break;
            case 2:
            musicVolume = gui.buttonPosition(1, xpos);
            break;

            case 3:
            musicEnabled = (musicEnabled) ? false: true;
            break;

            case 4:
            soundVolume = gui.buttonPosition(4, xpos);
            break;
            case 5:
            soundVolume = gui.buttonPosition(4, xpos);
            break;

            case 6:
            soundEnabled = (soundEnabled) ? false: true;
            break;

            case 7:
            nextState = MENU_STATE;
            break;

            default:
            break;
        }
        music->setVolume(musicEnabled ? musicVolume : 0);
        data.stats["GameMusic"]["volume"] = musicVolume;
        data.stats["GameSound"]["volume"] = soundVolume;

    }

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