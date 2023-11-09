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
    void handleEvent      (sf::Event)          override;
    void updateLogic      (sf::Time const &) override;
    void renderFrame      (sf::RenderWindow &) override;
    int getNextState      ()                   override;
    void spawnFriendly    ();
    void spawnEnemy       ();
    void handleCollisions (sf::Time const &);

private:
    // VARIABLES
    std::deque<Entity*> friendlyQueue {};
    std::deque<Entity*> enemyQueue    {};

};

#endif