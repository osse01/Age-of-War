#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
    public:
        Entity(bool FRIENDLY);
        virtual ~Entity() = default;
        void handleCollison(sf::Time const & frameDuration);
        sf::Sprite render() const &;
        void updatePos(sf::Time const &);
        bool collides( Entity* const );

    private:
        void detectCollision();
        double xpos;
        double ypos;
        double movementSpeed;
        bool IS_FRIENDLY;
        bool hasCollided;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::RectangleShape boundingbox;
};

#endif