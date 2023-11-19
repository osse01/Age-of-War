#include "../include/Entity.h"

#include <iostream>

Entity::Entity(const FileReader::Data& stats, bool friendly, sf::Vector2f pos)
    
    : xpos { pos.x }, ypos { pos.y }, hp { stats.hp }, isFriendly { friendly }, 
      texture{}, rectSourceSprite { 0,128,128,128 }, sprite {texture, rectSourceSprite},
      boundingbox { sf::Vector2f ( stats.boxSize, stats.boxSize ) }
{
    if(!texture.loadFromFile(stats.filename))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in Entity::Entity().");
    }
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));
    boundingbox.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));

    sprite.setPosition( xpos, ypos );
    boundingbox.setPosition( xpos, ypos );
    if(isFriendly)
    {
        sprite.setScale(sf::Vector2f(-1.f,1.f));
    }
}

sf::Sprite Entity::getSprite() const &
{
    return sprite;
}

bool Entity::collides( std::shared_ptr<Entity> other )
{
    // Check whether this collides with other
    return boundingbox.getGlobalBounds().intersects(
            ( other->boundingbox.getGlobalBounds() ) );
}
bool Entity::isDead()
{
    return hp <= 0;
}