#ifndef WINSTATE_H
#define WINSTATE_H

#include "State.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

class WinState: public State
{
    public:
    // CONSTRUCTORS / DESTRUCTORS
    WinState(std::shared_ptr<sf::RenderWindow>, FileReader::Data&, std::shared_ptr<sf::Music>, std::shared_ptr<sf::Time>, sf::Texture);
    ~WinState() override;
    WinState(const WinState&) = delete;
    WinState& operator= (const WinState&) = delete;

    // FUNCTIONS
    void handleEvent (sf::Event) override;
    void updateLogic ()          override;
    void renderFrame ()          override;
    int getNextState ()          override;
    void resetState ()           override;

    private:
    int nextState;

    sf::Font*           textFont;
    sf::Text*           winText;
    sf::RectangleShape* greyOut;
    sf::Texture         gamestateFrameTexture;
    sf::Sprite          gamestateFrameSprite;

};

#endif