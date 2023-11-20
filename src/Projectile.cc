#include "../include/Projectile.h"
#include "cmath"
#include "math.h"
#include <iostream>

Projectile::Projectile(const FileReader::Data& data, bool friendly, sf::Vector2f pos)
: Dynamic::Dynamic(data, friendly, pos), g{10}, counter {0}
{
    Entity::sprite.setRotation( 45 );
}

void Projectile::handleCollision(__attribute__((unused)) int, 
                                __attribute__((unused)) int)
{}

void Projectile::updatePos()
{
    Entity::xpos += Dynamic::MOVEMENTSPEED;
    Entity::ypos -=  Dynamic::MOVEMENTSPEED - 
                        std::pow(counter,2)*g/2;
                        
    Entity::sprite.setRotation( atan2(-Dynamic::MOVEMENTSPEED + std::pow(counter,2)*g/2,
            Dynamic::MOVEMENTSPEED) * 180/3.14);
    counter += 0.03;
    
    
    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);
    Entity::sprite.setTextureRect(Entity::rectSourceSprite);

}