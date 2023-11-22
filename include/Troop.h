#ifndef TROOP_H
#define TROOP_H

#include <SFML/Graphics.hpp>
#include "Dynamic.h"

class Troop : public Dynamic
{
    public:
        Troop(const FileReader::Data&, bool, sf::Vector2f);
        virtual ~Troop() = default;

        void handleCollision(int, int, std::shared_ptr<sf::Time>) override;
        void updatePos(std::shared_ptr<sf::Time> frameDuration)          override;

    private:
        void changeSprite();
        void walk();
        void idle();
        void attack(int, std::shared_ptr<sf::Time>);
        int damageCounter;
};

#endif