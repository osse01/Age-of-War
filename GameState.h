#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"



class GameState : public State
//  =============   GameState CLASS    ===============
{
public:
    // CONSTRUCTORS
    GameState();
    virtual ~GameState() = 0;

    // FUNCTIONS
    void handleEvent     (sf::Event);
    void updateLogic     ();
    void renderFrame     ();
    int getNextGameState ();


};

#endif