#include "../include/Entity.h"

#include <iostream>


Entity::Entity(const FileReader::Data& stats, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    
    : xpos { pos.x }, ypos { pos.y }, hp { stats.hp }, isFriendly { friendly }, hasCollided { false },
      texture{}, rectSourceSprite { 0,0,stats.spriteDim.x,stats.spriteDim.y }, sprite {texture, rectSourceSprite},
      boundingbox { stats.boxSize }, frameDuration {frameDuration}
{
    if(!texture.loadFromFile(stats.filename))
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
        sprite.setScale(sf::Vector2f(-1.f,1.f));
    }
}

bool Entity::collides( std::shared_ptr<Entity> other )
{
    // Check whether this collides with other
    hasCollided = boundingbox.getGlobalBounds().intersects(
            ( other->boundingbox.getGlobalBounds() ) );
    other->hasCollided = hasCollided;

    return hasCollided;
}

sf::Sprite Entity::getSprite() const &
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