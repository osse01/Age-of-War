#ifndef TROOP_H
#define TROOP_H

#include <SFML/Graphics.hpp>
#include "Dynamic.h"

class Troop : public Dynamic
{
    public:
        Troop(const FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
        virtual ~Troop() = default;

        void handleCollision(int, int) override;
        void updatePos()          override;
        virtual std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&, std::shared_ptr<sf::Time>, sf::Vector2f) = 0;


    protected:
        void changeSprite();
        void walk();
        void idle();
        void attack();
        void takeDamage(int);
        int   damageCounter;
        int   spriteCounter;
        float collisionCounter;
};

#endif