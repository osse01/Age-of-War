#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

#include "State.h"
#include "GUI.h"

class OptionsState : public State
// A state for the options menu
// This class handles all the logic for the options menu and is responsible for the sound options
{
    public:
    OptionsState(std::shared_ptr<sf::RenderWindow>, FileReader::Data&, std::shared_ptr<sf::Music>, 
                 std::map<std::string, std::shared_ptr<sf::Sound>>, std::shared_ptr<sf::Time>, sf::Texture);
    ~OptionsState();
    OptionsState(const OptionsState&) = delete;
    OptionsState(OptionsState&&) = delete;

    // Functions
    void handleEvent(sf::Event) override;
    void renderFrame() override;
    int getNextState() override;
    void updateLogic() override;
    void resetState() override;
    void prevState(int) override;

    private:
    GUI       gui;
    FileReader::Data& data;
    sf::Texture lastFrameTexture;
    sf::Sprite lastFrameSprite;
    int       nextState;
    float       soundVolume;
    float       musicVolume;
    bool      soundEnabled;
    bool      musicEnabled;
    bool      buttonPressed;
    int       buttonNumber;
    int       previousState;




};
#endif