#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "FileReader.h"
#include "memory"

class Entity
{
    public:
         Entity(const FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
        virtual ~Entity() = default;
        
        virtual void handleCollision(int, int) = 0;
        virtual void updatePos()       = 0;
        virtual int getDamage()        = 0;
        virtual int getType()          = 0;
        int incrAtkCounter();
        void resetAtkCounter();
        sf::Vector2f getPos();
        bool isDead();

        sf::Sprite getSprite()         const &;
        bool collides( std::shared_ptr<Entity> );

    protected:
        int                 atkCounter {0};
        double              xpos;
        double              ypos;
        int                 hp;
        bool                isFriendly;
        bool                hasCollided;
        sf::Texture         texture;
        sf::IntRect         rectSourceSprite;
        sf::Sprite          sprite;
        sf::RectangleShape  boundingbox;
        std::shared_ptr<sf::Time> frameDuration;
};

#endif