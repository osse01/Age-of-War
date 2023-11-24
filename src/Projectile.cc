#include "../include/Projectile.h"
#include "cmath"
#include <iostream>

Projectile::Projectile(const FileReader::Data& data, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: DAMAGE { data.damage }, MOVEMENTSPEED { data.movementSpeed }, xpos { pos.x }, ypos { pos.y }, hp { data.hp }, 
  isFriendly { friendly }, hasCollided { false }, texture {}, sprite {}, boundingbox { data.boxSize },
  frameDuration { frameDuration }, counter { 0 }
{
    if(!texture.loadFromFile(data.filename))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find texture image. Error in Projectile::Projectile.");
    }
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));
    boundingbox.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));

    sprite.setPosition( xpos, ypos );
    boundingbox.setPosition( xpos, ypos );
    if(isFriendly)
    {
        sprite.setScale(sf::Vector2f(-0.8f,0.8f));
    }
    sprite.setRotation( -45 );
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
    xpos += MOVEMENTSPEED * 3 * frameDuration->asSeconds();
    ypos -= (MOVEMENTSPEED - 
                        std::pow(counter,2)*g/2)*0.2 * frameDuration->asSeconds();
                        
    sprite.setRotation( atan2( (-MOVEMENTSPEED + std::pow(counter,2)*g/2) * 0.2,
            MOVEMENTSPEED * 3 ) * 180/3.14);
    counter += 0.1;
    
    
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


sf::Sprite Projectile::getSprite() const &
{
    return sprite;
}