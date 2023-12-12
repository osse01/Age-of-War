#include "../include/OptionsState.h"

OptionsState::OptionsState(std::shared_ptr<sf::RenderWindow> window, FileReader::Data& data, std::shared_ptr<sf::Music> music, 
                           std::map<std::string, std::shared_ptr<sf::Music>> sound, std::shared_ptr<sf::Time> frameDuration, sf::Texture lastFrame)
: State{window, data, music, sound, frameDuration}, 
  gui{OPTIONS_STATE, window, data}, data { data }, lastFrameTexture { lastFrame }, lastFrameSprite {},
  nextState {OPTIONS_STATE},
  soundVolume {data.stats["GameSound"]["volume"]}, musicVolume {data.stats["GameMusic"]["volume"]}, 
  soundEnabled { data.stats["GameSound"]["enabled"] }, musicEnabled { data.stats["GameMusic"]["enabled"] },
  buttonPressed { false }, buttonNumber { 0 }, previousState {}
{
    music->play();
    lastFrameSprite.setTexture(lastFrameTexture);
}

OptionsState::~OptionsState()
{
    music->stop();
}

void OptionsState::handleEvent(sf::Event event)
// Handle Option Events 
// such as Sound Volume, Music Volume and Sound Enabled
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
        
        // Set Music and Volume from Mouse Input
        switch(buttonNumber)
        {
            case 1:
            musicVolume = gui.sliderPosition(1, xpos);
            data.stats["GameMusic"]["volume"] = musicVolume;
            break;
            case 2:
            musicVolume = gui.sliderPosition(1, xpos);
            data.stats["GameMusic"]["volume"] = musicVolume;
            break;

            case 3:
            musicEnabled = !musicEnabled;
            data.stats["GameMusic"]["enabled"] = musicEnabled;
            sound["toggle"]->stop();
            sound["toggle"]->play();
            break;

            case 4:
            soundVolume = gui.sliderPosition(4, xpos);
            data.stats["GameSound"]["volume"] = soundVolume;
            break;
            case 5:
            soundVolume = gui.sliderPosition(4, xpos);
            data.stats["GameSound"]["volume"] = soundVolume;
            break;

            case 6:
            soundEnabled = !soundEnabled;
            data.stats["GameSound"]["enabled"] = soundEnabled;
            sound["toggle"]->stop();
            sound["toggle"]->play();
            break;

            case 7:
            nextState = previousState;
            break;

            default:
            break;
        }
        music->setVolume(musicEnabled ? musicVolume : 0);
        sound["button"]->setVolume(soundEnabled ? soundVolume : 0);
        sound["toggle"]->setVolume(soundEnabled ? soundVolume : 0);
        sound["buyTurret"]->setVolume(soundEnabled ? soundVolume : 0);
    }

}

void OptionsState::renderFrame()
// A function to render the Options State
{
    window->clear();
    window->draw(lastFrameSprite);
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

void OptionsState::prevState(int previousState)
{
    OptionsState::previousState = previousState;
}