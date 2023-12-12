#ifndef LOSESTATE_H
#define LOSESTATE_H

#include "State.h"
#include <memory>
#include "GUI.h"

#include <SFML/Graphics.hpp>
#include <string>

class LoseState: public State
{
    public:
    // CONSTRUCTORS / DESTRUCTORS
    LoseState(std::shared_ptr<sf::RenderWindow>, FileReader::Data&, std::shared_ptr<sf::Music>, 
              std::map<std::string, std::shared_ptr<sf::Sound>>, std::shared_ptr<sf::Time>, sf::Texture&);
    ~LoseState() override;
    LoseState(const LoseState&) = delete;
    LoseState& operator= (const LoseState&) = delete;

    // FUNCTIONS
    void handleEvent (sf::Event) override;
    void updateLogic ()          override;
    void renderFrame ()          override;
    int getNextState ()          override;
    void resetState ()           override;

    private:
    int nextState;

    sf::Font            textFont;
    sf::Text            loseText;
    sf::RectangleShape  greyOut;
    sf::Texture         gamestateFrameTexture;
    sf::Sprite          gamestateFrameSprite;

    GUI     gui;
};

#endif