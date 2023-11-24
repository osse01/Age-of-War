#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>



int const MENU_STATE    { 0 };
int const GAME_STATE    { 1 };
int const PAUSE_STATE   { 2 };
int const WIN_STATE   { 3 };
int const LOSE_STATE   { 4 };

class State
//  =============   State CLASS    ===============
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    State(std::shared_ptr<sf::RenderWindow>, std::shared_ptr<sf::Music>, std::shared_ptr<sf::Time>);
    virtual ~State();
    State(const State&) = delete;
    State& operator= (const State&) = delete;

    // FUNCTIONS
    virtual void handleEvent (sf::Event) = 0;
    virtual void updateLogic ()          = 0;
    virtual void renderFrame ()          = 0;
    virtual int getNextState ()          = 0;
    virtual void resetState ()           = 0;

protected:
    std::shared_ptr<sf::RenderWindow>   window;
    std::shared_ptr<sf::Music> music{};
    std::shared_ptr<sf::Time> frameDuration{};
};

#endif