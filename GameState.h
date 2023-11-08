#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Entity.h"

#include <queue>



class GameState : public State
//  =============   GameState CLASS    ===============
{
public:
    // CONSTRUCTORS
    GameState  () = default;
    ~GameState () = default;
 
    // FUNCTIONS
    void handleEvent   (sf::Event)          override;
    void updateLogic   ()                   override;
    void renderFrame   (sf::RenderWindow &) override;
    int getNextState   ()                   override;
    void spawnFriendly ();

private:
    // VARIABLES
    std::deque<Entity*> friendlyQueue {};

};

#endif