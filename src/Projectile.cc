#include "../include/Projectile.h"
#include "cmath"
#include <iostream>

Projectile::Projectile(FileReader::Data& data, std::string projectileType, bool friendly, sf::Vector2f pos, float angle, std::shared_ptr<sf::Time> frameDuration)
: DAMAGE { data.stats[projectileType]["damage"] }, MOVEMENTSPEED { data.stats[projectileType]["movementSpeed"] }, 
  INITIAL_ANGLE {angle}, xpos { pos.x }, ypos { pos.y }, dx {0}, dy {0}, x0 {xpos}, y0 {ypos}, hp { data.stats[projectileType]["hp"] }, 
  isFriendly { friendly }, hasCollided { false }, elapsedTime { 0 }, texture {}, sprite {}, boundingbox { data.boxSize[projectileType] },
  frameDuration { frameDuration }, counter { 0 }
{
    if(!texture.loadFromFile(data.files[projectileType]))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find texture image. Error in Projectile::Projectile.");
    }
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2.f,sprite.getGlobalBounds().height/2.f));
    boundingbox.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2.f,sprite.getGlobalBounds().height/2.f));

    sprite.setPosition( xpos, ypos );
    boundingbox.setPosition( xpos, ypos );
    if(isFriendly)
    {
        sprite.setScale(sf::Vector2f(-0.8f,0.8f));
    }
    sprite.setRotation( -45.f );
}

bool Projectile::collides( sf::RectangleShape other )
{
    // Check whether this collides with other
    hasCollided = boundingbox.getGlobalBounds().intersects(
            ( other.getGlobalBounds() ) );
    return hasCollided;
}

void Projectile::handleCollision()
{
   hp = 0;
}

void Projectile::updatePos()
{

    elapsedTime += frameDuration->asSeconds(); 

    dx = MOVEMENTSPEED * cos(3.14*INITIAL_ANGLE/180.f) * frameDuration->asSeconds();
    dy = -MOVEMENTSPEED * sin(3.14*INITIAL_ANGLE/180.f) * frameDuration->asSeconds() + g * elapsedTime * frameDuration->asSeconds();

    if (!isFriendly)
    {
        dx = -dx;
    }

    xpos += dx;
    ypos += dy;
           
    sprite.setRotation( atan2(dy, dx) * 180/3.14);  
    if (!isFriendly)
    {
        sprite.setRotation(180 - sprite.getRotation());
    }  
    
    sprite.setPosition(xpos, ypos);
    boundingbox.setPosition(xpos, ypos);
}

int Projectile::getDamage()
//  ---------------------------------------------
//  Returns the Dynamic object DAMAGE variable.
//  ---------------------------------------------
{
  return DAMAGE;
}


bool Projectile::getIsFriendly()
{
    return isFriendly;
}


int Projectile::getDeathValue()
{
    return 0;
}

float Projectile::getRange()
{
    return 0;
}

bool Projectile::isDead()
{
    return hp == 0;
}


sf::Sprite & Projectile::getSprite()
{
    return sprite;
}