#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    public:
        Entity(bool FRIENDLY);
        virtual ~Entity() = default;
        void handleCollison();
        sf::RectangleShape render();
        void updatePos();

    private:
        void detectCollision();
        double xpos;
        double ypos;
        double MVMSPD;
        bool IS_FRIENDLY;
        bool hasCollided;
        sf::RectangleShape rekt;
};

#endif