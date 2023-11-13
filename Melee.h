#ifndef MELEE_H
#define MELEE_H

#include <SFML/Graphics.hpp>
#include "Troop.h"



class Melee : public Troop
{
    public:
        Melee(Stats&);
        virtual ~Melee() = default;

        void changeWalkSprite();
        void changeIdleSprite();
        void changeAttackSprite();
    
    private:
        std::string walkSprite;
        
        struct Stats
        {
            double             xpos;
            double             ypos;
            bool               isFriendly;
            int                hp;
            int                movementSpeed;
            int                damage;
            int                deathValue;
            int                buyValue;
            int                range;
            sf::Sprite         sprite;
            sf::RectangleShape boundingbox;
            std::string        texturePath;
};

};

#endif