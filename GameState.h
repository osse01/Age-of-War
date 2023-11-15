#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Melee.h"
#include "Troop.h"
#include "Dynamic.h"
#include "Entity.h"
#include "FileReader.h"
#include "GUI.h"

#include <SFML/Audio.hpp>

#include <queue>



class GameState : public State
//  =============   GameState CLASS    ===============
{
    public:
        // CONSTRUCTORS
        GameState  (sf::RenderWindow*, int*, sf::Music*, sf::Time*);
        ~GameState () override;
        GameState (const GameState&) = delete;

        GameState& operator= (const GameState&) = delete;
    
    
        // FUNCTIONS
        void handleEvent      (sf::Event) override;
        void updateLogic      ()          override;
        void renderFrame      ()          override;
        int getNextState      ()          override;
        void spawnFriendly    ();
        void spawnEnemy       ();
        void handleCollisions ();

    private:
        // VARIABLES
        FileReader::Data melee;
        FileReader::Data ranged;
        FileReader::Data tank;

        std::deque<Entity*> friendlyQueue {};
        std::deque<Entity*> enemyQueue    {};

        std::string         backgroundFile;

        sf::RenderWindow*   window;

        sf::Texture         backgroundTexture;
        sf::Sprite          backgroundSprite;
        
        sf::Vector2f        zoomFactor;

        GUI                 gui;

        int* currentState;
};

#endif