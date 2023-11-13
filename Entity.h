#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

class Entity
{
    public:
         Entity(bool, double, double, int, sf::Sprite &,
                sf::RectangleShape &, std::string &);
        virtual ~Entity() = default;
        
        virtual void handleCollison() = 0;
        virtual void updatePos()      = 0;

        sf::Sprite getSprite()         const &;
        bool collides( Entity* const ) const;

    protected:
        double              xpos;
        double              ypos;
        int                 hp;
        bool                IS_FRIENDLY;
        const sf::Texture   TEXTURE;
        sf::Sprite          sprite;
        sf::RectangleShape  boundingbox;
};

#endif