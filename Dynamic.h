#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Dynamic : public Entity
{
    public:
        Dynamic(const FileReader::Data&, bool, sf::Vector2f);
        virtual ~Dynamic() = default;

        virtual void handleCollision(int)   = 0;
        virtual void updatePos()           = 0;

    protected:
        const int MOVEMENTSPEED;
        const int DAMAGE;
        const int DEATH_VALUE;
        const int BUY_VALUE;
        const int RANGE;

};

#endif