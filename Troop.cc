#include "Troop.h"

Troop::Troop(stats stats)
:Dynamic( 30, 1, 1, 1, 1 )
{}

void handleCollision(int troopState)
{
    switch ( troopState ) {
        case idle:
            changeIdleSprite();
            break;
        case attack:
            changeAttackSprite();
            break;
        default:
            throw std::logic_error("    >>Error: The troopState does not exist!");
    }
}

void updatePos()
{
    Entity::xpos += Dynamic::MOVEMENTSPEED;
    changeWalkSprite();
}