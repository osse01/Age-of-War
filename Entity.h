#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "FileReader.h"

class Entity
{
    public:
         Entity(const FileReader::Data&, bool, sf::Vector2f);
        virtual ~Entity() = default;
        
        virtual void handleCollision(int) = 0;
        virtual void updatePos()      = 0;

        sf::Sprite getSprite()         const &;
        bool collides( Entity* const );

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