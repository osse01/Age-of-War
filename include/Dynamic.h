#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Dynamic : public Entity
{
    public:
        Dynamic(const FileReader::Data&, bool, sf::Vector2f);
        virtual ~Dynamic() = default;

        virtual void handleCollision(int, int, std::shared_ptr<sf::Time>)   = 0;
        virtual void updatePos(std::shared_ptr<sf::Time> frameDuration)           = 0;
        int getDamage() override;

    protected:
        const int DAMAGE;
        const float MOVEMENTSPEED;
        const float RANGE;
        const int ATTACK_SPEED;
        const int DEATH_VALUE;
        const int BUY_VALUE;

};

#endif