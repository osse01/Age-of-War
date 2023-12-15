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

int const PAUSE             { 1 };
int const SPECIAL_ABILITY   { 2 };
int const BUY_TURRET        { 3 };
int const SPAWN_TANK        { 4 };
int const SPAWN_RANGED      { 5 }; 
int const SPAWN_MELEE       { 6 };



class GameState : public State
//  =============   GameState CLASS    ===============
{
    public:
        // CONSTRUCTORS
        GameState  (std::shared_ptr<sf::RenderWindow>, FileReader::Data&, std::shared_ptr<sf::Music>, 
                    std::map<std::string, std::shared_ptr<sf::Sound>>, std::shared_ptr<sf::Time>);
        ~GameState () override;
        GameState (const GameState&) = delete;

        GameState& operator= (const GameState&) = delete;
    
    

    private:
        //  FUNCTIONS
        void handleEvent      (sf::Event) override;
        void updateLogic      ()          override;
        void renderFrame      ()          override;
        int  getNextState     ()          override;
        void resetState       ()          override;

        void windowPanning     (bool);
        void enemyPlay        ();
        void spawnFriendly    (std::string);
        void spawnEnemy       (int);
        void handleCollisions ();

        // VARIABLES

        std::vector<std::shared_ptr<Entity>>      friendlyVector;
        std::vector<std::shared_ptr<Entity>>      enemyVector;
        std::vector<std::shared_ptr<Projectile>>  projectileVector;

        sf::Texture         backgroundTexture;
        sf::Texture         groundTexture;
        sf::Texture         woodsTexture;
        sf::Sprite          backgroundSprite;
        sf::Sprite          groundSprite;
        sf::Sprite          woodsSprite;
        sf::View            view;
        
        sf::Vector2f        zoomFactor;

        int nextState;
        int gold;
        bool turretAvailable;
        
        GUI                 gui;
        FileReader::Data    enemyStats;
        Enemy               enemy;
        std::vector<int>    deleteEntities{};
};

#endif