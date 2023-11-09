#ifndef ENTITY_H
#define ENTITY_H

class Entity
//  =============   Entity CLASS    ===============
{
    public:
    // CONSTRUCTORS
        Entity          (bool FRIENDLY);
        virtual ~Entity() = default;

    // FUNCTIONS
        void handleCollison       ();
        sf::RectangleShape render ();
        void updatePos            ();
        bool collides (Entity* const other);



    private:
    // FUNCTIONS
        void detectCollision      ();

    // VARIABLES   
        double xpos;
        double ypos;
        double movementSpeed;
        bool IS_FRIENDLY;
        bool hasCollided;
        sf::RectangleShape rekt;
};

#endif