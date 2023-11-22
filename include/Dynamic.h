#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Dynamic : public Entity
{
    public:
        Dynamic(const FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
        virtual ~Dynamic() = default;

        virtual void handleCollision(int, int)   = 0;
        virtual void updatePos()                 = 0;
        virtual int getType()                    = 0;
        int incrAtkCounter(){return 0;};
        void resetAtkCounter(){};

        int getDamage();

    protected:
        const int DAMAGE;
        const float MOVEMENTSPEED;
        const float RANGE;
        const int ATTACK_SPEED;
        const int DEATH_VALUE;
        const int BUY_VALUE;

};
#endif