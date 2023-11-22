#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "FileReader.h"
#include "State.h"
#include "Melee.h"
#include "Range.h"
#include "Troop.h"
#include "Dynamic.h"
#include "Entity.h"
#include "Projectile.h"
#include "GUI.h"

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
            void spawnEnemy       ();
            void handleCollisions ();
            void resetState       ()          override;
            void updateStage      ();

    private:
        // VARIABLES
        FileReader::Data melee;
        FileReader::Data ranged;
        FileReader::Data tank;
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
        std::vector<int> deleteEntities{};
};

#endif