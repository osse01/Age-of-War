#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Melee.h"
#include "Ranged.h"
#include "Tank.h"
#include "Troop.h"
#include "Dynamic.h"
#include "Entity.h"
#include "Projectile.h"
#include "GUI.h"
#include "Enemy.h"
#include "Base.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <queue>
#include <memory>
#include <string>




class GameState : public State
//  =============   GameState CLASS    ===============
{
    public:
        // CONSTRUCTORS
        GameState  (std::shared_ptr<sf::RenderWindow>, FileReader::Data&, std::shared_ptr<sf::Music>, std::shared_ptr<sf::Time>);
        ~GameState () override;
        GameState (const GameState&) = delete;

        GameState& operator= (const GameState&) = delete;
    
    
        // FUNCTIONS
        void handleEvent      (sf::Event) override;
        void updateLogic      ()          override;
        void renderFrame      ()          override;
        int  getNextState     ()          override;
        void spawnFriendly    (std::string);
        void spawnEnemy       (int);
        void handleCollisions ();
        void resetState       ()          override;
        void updateStage      ();
        void enemyPlay        ();

    private:
        // VARIABLES

        std::vector<std::shared_ptr<Entity>> friendlyVector;
        std::vector<std::shared_ptr<Entity>> enemyVector;
        std::deque<std::shared_ptr<Projectile>> projectileQueue;

        sf::Texture         backgroundTexture;
        sf::Texture         groundTexture;
        sf::Sprite          backgroundSprite;
        sf::Sprite          groundSprite;
        sf::View            view;
        sf::RenderWindow    canvas;
        
        sf::Vector2f        zoomFactor;

        int nextState;
        int stage;
        int gold;
        GUI                 gui;
        Enemy               enemy;
        std::vector<int>    deleteEntities{};
};

#endif