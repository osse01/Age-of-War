#include "../include/Projectile.h"
#include "cmath"
#include <iostream>

Projectile::Projectile(const FileReader::Data& data, bool friendly, sf::Vector2f pos)
: Dynamic::Dynamic(data, friendly, pos), g{10}, counter {0}
{
    std::cout << data.filename << std::endl;
}

void Projectile::handleCollision(__attribute__((unused)) int, 
                                __attribute__((unused)) int)
{}

void Projectile::updatePos()
{
    Entity::xpos += Dynamic::MOVEMENTSPEED;
    Entity::ypos -=  14 * std::sin(counter) - 
                        std::pow(counter,2)*g/2;
                        
    Entity::sprite.setRotation(-14*std::cos(counter) + counter * g);
    counter += 0.03;

    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);
}