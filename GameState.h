#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Entity.h"

#include <SFML/Audio.hpp>

#include <queue>



class GameState : public State
//  =============   GameState CLASS    ===============
{
public:
    // CONSTRUCTORS
    GameState  (sf::RenderWindow*, int*, sf::Music*);
    ~GameState ();
    GameState (const GameState&) = delete;

    GameState operator= (const GameState&) = delete;
 
 
    // FUNCTIONS
    void handleEvent      (sf::Event)           override;
    void updateLogic      (sf::Time const &)    override;
    void renderFrame      ()                    override;
    int getNextState      ()                    override;
    void spawnFriendly    ();
    void spawnEnemy       ();
    void handleCollisions (sf::Time const &);

    // VARIABLES
    std::deque<Entity*> friendlyQueue {};
    std::deque<Entity*> enemyQueue    {};

    std::string     backgroundFile;

    sf::RenderWindow*   window;

    sf::Texture        backgroundTexture;
    sf::Sprite         backgroundSprite;
    
    sf::Vector2f        zoomFactor;



    int* currentState;
    sf::Music* music;
};

#endif