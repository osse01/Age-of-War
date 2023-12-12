#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <experimental/random>
#include "memory"


#include "Projectile.h"
#include "FileReader.h"

class Entity
{
    public:
         Entity(FileReader::Data&, std::string, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
        virtual ~Entity() = default;
        
        virtual std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&,
                                                            std::shared_ptr<sf::Time>, 
                                                            sf::Vector2f);
        virtual void    handleCollision(int = 0, int = 0) = 0;
        virtual void    updatePos()       = 0;
        virtual int     getDamage()     {return 0;};
        virtual int     getDeathValue() {return 0;};
        virtual bool    inRange( std::shared_ptr<Entity> )    = 0;
        virtual void    specialAttack() {};
        virtual float   getCurrentCooldown() {return 0.f;};

        int     getHP();
        sf::RectangleShape getBox();
        void playSound(std::map<std::string, std::shared_ptr<sf::Sound>>);

        bool getIsFriendly();
        bool isDead();

        virtual sf::Sprite& getSprite();
        bool        collides( std::shared_ptr<Entity> );
        virtual bool buyTurret(FileReader::Data&, bool, std::shared_ptr<sf::Time>, std::map<std::string, std::shared_ptr<sf::Sound>>){return true;};

    protected:
        float              xpos;
        float              ypos;
        float                 hp;
        bool                isFriendly;
        bool                hasCollided;

        int   actionState;
        int   spriteCounter;
        int   audioNumber;
        

        sf::Texture         texture;
        sf::IntRect         rectSourceSprite;
        sf::Sprite          sprite;
        sf::RectangleShape  boundingbox;
        std::shared_ptr<sf::Time> frameDuration;
};

#endif