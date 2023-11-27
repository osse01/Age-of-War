#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "State.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>
#include <list>


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
    void    setupCanvas    ();

    private:
    int     nextState;
    double  elapsedTime;

    std::list<sf::Text> nameList;

    sf::Font            font;
    sf::Texture         backgroundTexture;
    sf::Sprite          backgroundSprite;
    sf::RenderTexture  canvas;

};

#endif