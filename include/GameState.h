#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "FileReader.h"
#include "State.h"
#include "Melee.h"
#include "Range.h"
#include "Tank.h"
#include "Troop.h"
#include "Dynamic.h"
#include "Entity.h"
#include "Projectile.h"
#include "GUI.h"
#include "Enemy.h"

#include <SFML/Audio.hpp>

#include <queue>
#include <memory>
#include <string>




class GameState : public State
//  =============   GameState CLASS    ===============
{
    public:
        // CONSTRUCTORS
        GameState  (std::shared_ptr<sf::RenderWindow>, std::shared_ptr<sf::Music>, std::shared_ptr<sf::Time>);
        ~GameState () override;
        GameState (const GameState&) = delete;

            GameState& operator= (const GameState&) = delete;
       
       
            // FUNCTIONS
            void handleEvent      (sf::Event) override;
            void updateLogic      ()          override;
            void renderFrame      ()          override;
            int  getNextState     ()          override;
            void spawnFriendly    (int);
            void spawnEnemy       (int);
            void handleCollisions ();
            void resetState       ()          override;
            void updateStage      ();
            void enemyPlay        ();

    private:
        // VARIABLES
        FileReader::Data meleeF;
        FileReader::Data rangedF;
        FileReader::Data meleeE;
        FileReader::Data rangedE;
        FileReader::Data tankF;
        FileReader::Data tankE;
        FileReader::Data projectile;


        std::deque<std::shared_ptr<Entity>> friendlyQueue;
        std::deque<std::shared_ptr<Entity>> enemyQueue;
        std::deque<std::shared_ptr<Entity>> projectileQueue;

        std::string         backgroundFile;

        sf::Texture         backgroundTexture;
        sf::Sprite          backgroundSprite;
        
        sf::Vector2f        zoomFactor;

        int nextstate;
        int stage;
        GUI                 gui;
        Enemy               enemy;
        std::vector<int> deleteEntities{};
};

#endif