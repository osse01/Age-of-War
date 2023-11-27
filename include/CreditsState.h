#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "State.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

class CreditsState: public State
{
    public:
    // CONSTRUCTORS / DESTRUCTORS
    CreditsState(std::shared_ptr<sf::RenderWindow>, std::shared_ptr<sf::Music>, std::shared_ptr<sf::Time>);
    ~CreditsState() override;
    CreditsState(const CreditsState&) = delete;
    CreditsState& operator= (const CreditsState&) = delete;

    // FUNCTIONS
    void    handleEvent    (sf::Event) override;
    void    updateLogic    ()          override;
    void    renderFrame    ()          override;
    int     getNextState   ()          override;
    void    resetState     ()          override;  

    private:
    int     nextState;

    sf::Texture     backgroundTexture;
    sf::Sprite      backgroundSprite;

};

#endif