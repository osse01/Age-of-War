#ifndef TROOP_H
#define TROOP_H

#include <SFML/Graphics.hpp>
#include "Dynamic.h"

class Troop : public Dynamic
{
    public:
        Troop(stats&);
        virtual ~Troop() = default;

        void handleCollison(int);
        void updatePos();
        virtual void changeWalkSprite();
        virtual void changeIdleSprite();
        virtual void changeaAttackSprite();

    private:
        int walk   { 0 };
        int idle   { 1 };
        int attack { 2 };
};

#endif