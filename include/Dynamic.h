#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Dynamic : public Entity
{
    public:
        Dynamic(FileReader::Data&, std::string, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
        virtual ~Dynamic() = default;

        virtual void handleCollision(int, int)   = 0;
        virtual void updatePos()                 = 0;

        virtual int     getDamage()     override;
        int             getDeathValue() override;
        bool            inRange( std::shared_ptr<Entity> )      override;
        virtual void   showHP(std::shared_ptr<sf::RenderWindow>){};

    protected:
        const float   DAMAGE;
        const float   ATTACK_SPEED;
        const float   RANGE;
        const float   DEATH_VALUE;

};
#endif