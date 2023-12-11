#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Projectile.h"

#include "FileReader.h"
#include "memory"

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
        virtual float   getRange()          = 0;
        virtual void    specialAttack() {};

        int     getHP();
        sf::RectangleShape getBox();

        bool getIsFriendly();
        bool isDead();

        virtual sf::Sprite& getSprite();
        bool        collides( std::shared_ptr<Entity> );
        virtual bool buyTurret(FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>){return true;};

    protected:
        double              xpos;
        double              ypos;
        float                 hp;
        bool                isFriendly;
        bool                hasCollided;
        sf::Texture         texture;
        sf::IntRect         rectSourceSprite;
        sf::Sprite          sprite;
        sf::RectangleShape  boundingbox;
        std::shared_ptr<sf::Time> frameDuration;
};

#endif