#include "GameState"

class Entity
{
    public:
        Entity(bool FRIENDLY);
        ~Entity() = default;
        void handleCollison();
        render();

    private:
        void detectCollision();
        double xpos;
        double ypos;
        double MVMSPD;
        bool IS_FRIENDLY;
        bool hasCollided;
        sf::RectangleShape rekt;
}