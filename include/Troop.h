#ifndef TROOP_H
#define TROOP_H

#include <SFML/Graphics.hpp>
#include "Dynamic.h"

class Troop : public Dynamic
{
    public:
        Troop(const FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
        virtual ~Troop() = default;

        virtual std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&, std::shared_ptr<sf::Time>, sf::Vector2f);
        int     getDamage()               override;
        void    handleCollision(int, int) override;
        void    updatePos()               override;


    protected:
        void changeSprite(int);
        void takeDamage(int);
        int   spriteCounter;
        float collisionCounter;
};

#endif