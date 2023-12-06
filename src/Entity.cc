#include "../include/Entity.h"

#include <iostream>


Entity::Entity(FileReader::Data& data, std::string troopType, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    
    : xpos { pos.x }, ypos { pos.y }, hp { data.stats[troopType]["hp"] }, isFriendly { friendly }, hasCollided { false },
      texture{}, rectSourceSprite { sf::Vector2i(0,0),data.spriteDim[troopType] }, sprite {texture, rectSourceSprite},
      boundingbox { (data.boxSize[troopType]) }, frameDuration {frameDuration}
{
    std::string friendOrFoe = (isFriendly) ? "friendly_" : "enemy_";
    if(!texture.loadFromFile("assets/" + friendOrFoe + data.files[troopType]))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in Entity::Entity().");
    }
    sprite.setTextureRect(rectSourceSprite);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));
    boundingbox.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));

    sprite.setPosition( xpos, ypos );
    boundingbox.setPosition( xpos, ypos );
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
    || ( ((isFriendly ? 1 : -1)*(boundingbox.getGlobalBounds().left - other->boundingbox.getGlobalBounds().left)) > 0 ) ;
    other->hasCollided = hasCollided;

    return hasCollided;
}

sf::Sprite& Entity::getSprite()
{
    return sprite;
}

bool Entity::isDead()
{
    return hp <= 0;
}

bool Entity::getIsFriendly()
{
    return isFriendly;
}

sf::RectangleShape Entity::getBox() 
{
    return boundingbox;
}

int Entity::getHP()
{
    return hp;
}

std::shared_ptr<Projectile> Entity::spawnProjectile(FileReader::Data& stats,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f pos)
{
   std::shared_ptr<Projectile> projectile {};

   return projectile;
}