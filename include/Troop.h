#ifndef TROOP_H
#define TROOP_H

#include <SFML/Graphics.hpp>
#include "Dynamic.h"

class Troop : public Dynamic
{
    public:
        Troop(FileReader::Data&, std::string, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
        virtual ~Troop() = default;

        
        int   getDamage()               override;
        void    handleCollision(int, int) override;
        void    updatePos()               override;


    protected:
        void changeSprite();
        void takeDamage(int);
        int troopState;
        int   spriteCounter;
        float collisionCounter;
        const float MOVEMENTSPEED;

        const static int WALK   { 0 };
        const static int IDLE   { 1 };
        const static int ATTACK { 2 };
        const static int TAKE_DAMAGE { 3 };
};

#endif