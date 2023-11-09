#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    public:
        Entity(bool FRIENDLY);
        virtual ~Entity() = default;
        void handleCollison(sf::Time const & frameDuration);
        sf::RectangleShape render();
        void updatePos(sf::Time const &);
        bool collides( Entity* const );

    private:
        void detectCollision();
        double xpos;
        double ypos;
        double movementSpeed;
        bool IS_FRIENDLY;
        bool hasCollided;
        sf::RectangleShape rekt;
};

#endif