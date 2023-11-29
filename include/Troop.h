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
        void changeSprite();
        void takeDamage(int);
        int troopState;
        int   spriteCounter;
        float collisionCounter;

        const static int WALK   { 0 };
        const static int IDLE   { 1 };
        const static int ATTACK { 2 };
        const static int TAKE_DAMAGE { 3 };
};

#endif