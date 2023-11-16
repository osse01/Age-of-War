#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "FileReader.h"
#include "memory"

class Entity
{
    public:
         Entity(const FileReader::Data&, bool, sf::Vector2f);
        virtual ~Entity() = default;
        
        virtual void handleCollision(int, int) = 0;
        virtual void updatePos()      = 0;
        virtual int getDamage()       = 0;
        bool isDead();

        sf::Sprite getSprite()         const &;
        bool collides( std::shared_ptr<Entity> );

    protected:
        double              xpos;
        double              ypos;
        int                 hp;
        bool                isFriendly;
        sf::Texture         texture;
        sf::IntRect         rectSourceSprite;
        sf::Sprite          sprite;
        sf::RectangleShape  boundingbox;
};

#endif