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
        virtual int getType()           = 0;

    private:
        void changeSprite();
        void walk();
        void idle();
        void attack(int);
        int damageCounter;
        int spriteCounter;
};

#endif