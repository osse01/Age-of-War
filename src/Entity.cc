#include "../include/Entity.h"

#include <iostream>


Entity::Entity(FileReader::Data& data, std::string troopType, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    
    : xpos { pos.x }, ypos { pos.y }, hp { data.stats[troopType]["hp"] }, isFriendly { friendly }, hasCollided { false },
      actionState { 0 }, spriteCounter { 0 }, texture{}, rectSourceSprite { sf::Vector2i(0,0),data.spriteDim[troopType] },
      sprite {texture, rectSourceSprite},
      boundingbox { sf::Vector2f(data.boxSize[troopType].x, data.boxSize[troopType].y) },
      frameDuration {frameDuration}
{
    // Load Friendly or Enemy Image
    std::string friendOrFoe = (isFriendly) ? "friendly_" : "enemy_";
    if(!texture.loadFromFile("assets/" + friendOrFoe + data.files[troopType]))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in Entity::Entity().");
    }
    // Set Sprite Position
    sprite.setTextureRect(rectSourceSprite);

    float spriteBoxDiff {(sprite.getGlobalBounds().height-boundingbox.getGlobalBounds().height)/2};
    
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,boundingbox.getGlobalBounds().height + spriteBoxDiff));
    boundingbox.setOrigin(sf::Vector2f(boundingbox.getGlobalBounds().width/2,boundingbox.getGlobalBounds().height));

    sprite.setPosition( xpos, ypos );
    boundingbox.setPosition( xpos, ypos );
    boundingbox.setScale( data.windowScale, data.windowScale );

    // Mirror Friendly Sprite
    if(isFriendly)
    {
        sprite.setScale(sf::Vector2f(-data.windowScale,data.windowScale));
    }
    else
    {
        sprite.setScale(sf::Vector2f(data.windowScale,data.windowScale));
    }
}

bool Entity::collides( std::shared_ptr<Entity> other )
//  ---------------------------------------------
//  Checks if Unit has Collided and if we have lag.
//  ---------------------------------------------
{
    // Check whether this collides with other
    hasCollided = 
    boundingbox.getGlobalBounds().intersects(( other->boundingbox.getGlobalBounds()))
    || ( ((isFriendly ? 1 : -1)
       * (boundingbox.getGlobalBounds().left 
          - other->boundingbox.getGlobalBounds().left)) > 0 ) ;

    other->hasCollided = hasCollided;
    
    return hasCollided;
}

// Return Entity Sprite
sf::Sprite& Entity::getSprite()
{
    return sprite;
}

// Check if Entity is Dead
bool Entity::isDead()
{
    return hp <= 0;
}

// Return True if Friendly
bool Entity::getIsFriendly()
{
    return isFriendly;
}

// Return Entity Bounding Box
sf::RectangleShape Entity::getBox() 
{
    return boundingbox;
}

// Return Entity HP
int Entity::getHP()
{
    return hp;
}

// Virtual Function for spawnProjectile 
std::shared_ptr<Projectile> Entity::spawnProjectile(
    __attribute__((unused)) FileReader::Data&,
    __attribute__((unused)) std::shared_ptr<sf::Time>,
    __attribute__((unused)) sf::Vector2f)
{
   std::shared_ptr<Projectile> projectile {};

   return projectile;
}