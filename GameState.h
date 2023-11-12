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
    ~GameState () = default;
 
 
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
    std::string     treeFile;

    sf::RenderWindow*   window;
    sf::Image*          spriteImage;
    sf::Image*          backgroundImage;

    sf::Texture*        backgroundTexture;
    sf::Texture*        treeTexture;

    sf::Sprite*         backgroundSprite;
    sf::Sprite*         treeSprite;
    
    sf::Vector2f        zoomFactor;



    int* currentState;
    sf::Music* music;
};

#endif