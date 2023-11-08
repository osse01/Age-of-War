#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"



class GameState : public State
//  =============   GameState CLASS    ===============
{
public:
    // CONSTRUCTORS
    GameState() = default;
    ~GameState() = default;

    // FUNCTIONS
    void handleEvent     (sf::Event) override;
    void updateLogic     ()          override;
    void renderFrame     ()          override;
    int getNextState     ()          override;



};

#endif