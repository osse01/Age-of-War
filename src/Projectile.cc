#include "../include/Projectile.h"
#include "cmath"
#include <iostream>

Projectile::Projectile(FileReader::Data& data, std::string projectileType, bool friendly, sf::Vector2f pos, float angle, std::shared_ptr<sf::Time> frameDuration)
: DAMAGE { data.stats[projectileType]["damage"] }, MOVEMENTSPEED { data.stats[projectileType]["movementSpeed"] }, 
  INITIAL_ANGLE {angle}, xpos { pos.x }, ypos { pos.y }, dx {0.f}, dy {0.f}, x0 {xpos}, y0 {ypos}, hp { data.stats[projectileType]["hp"] }, 
  isFriendly { friendly }, hasCollided { false }, elapsedTime { 0.f }, texture {}, sprite {}, boundingbox { data.boxSize[projectileType] },
  frameDuration { frameDuration }
{
    // Load Projectile Image
    if(!texture.loadFromFile(data.files[projectileType]))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find texture image. Error in Projectile::Projectile.");
    }
    // Set Sprite Position
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2.f,sprite.getGlobalBounds().height/2.f));
    boundingbox.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2.f,sprite.getGlobalBounds().height/2.f));
    sprite.setPosition( xpos, ypos );
    boundingbox.setPosition( xpos, ypos );

    // Mirror Friendly Projectile
    if(isFriendly)
    {
        sprite.setScale(sf::Vector2f(-0.8f,0.8f));
    }
    sprite.setRotation( -45.f );
}

// Check whether this Collides with Other
bool Projectile::collides( sf::RectangleShape other )
{
    hasCollided = boundingbox.getGlobalBounds().intersects(
            ( other.getGlobalBounds() ) );
    return hasCollided;
}

// Reset HP to Zero after Collision
void Projectile::handleCollision()
{
   hp = 0;
}

// Update Projectile Position
void Projectile::updatePos()
{
    elapsedTime += frameDuration->asSeconds(); 

    dx = MOVEMENTSPEED * cos(3.14*INITIAL_ANGLE/180.f) * frameDuration->asSeconds();
    dy = -MOVEMENTSPEED * sin(3.14*INITIAL_ANGLE/180.f) * frameDuration->asSeconds() + g * elapsedTime * frameDuration->asSeconds();

    //  Set Opposite Direction for Enemies
    if (!isFriendly)
    {
        dx = -dx;
    }

    xpos += dx;
    ypos += dy;
                        
    sprite.setRotation( atan2(dy, dx) * 180/3.14);
    // Set Opposite Angle for Enemies
    if (!isFriendly)
    {
        sprite.setRotation(180 - sprite.getRotation());
    }  
    
    sprite.setPosition(xpos, ypos);
    boundingbox.setPosition(xpos, ypos);
}

// Return the Dynamic object DAMAGE variable
int Projectile::getDamage()
{
  return DAMAGE;
}

// Return True if Friendly
bool Projectile::getIsFriendly()
{
    return isFriendly;
}

// Check whether Projectile is Dead
bool Projectile::isDead()
{
    return hp == 0;
}

// Return Projectile Sprite
sf::Sprite & Projectile::getSprite()
{
    return sprite;
}