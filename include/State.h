#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


int const MENU_STATE    { 0 };
int const GAME_STATE    { 1 };
int const PAUSE_STATE   { 2 };

class State
//  =============   State CLASS    ===============
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    State(sf::Music*, sf::Time*);
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
    sf::Music* music{};
    sf::Time* frameDuration{};
};

#endif