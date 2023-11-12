#include "Entity.h"

#include <iostream>

unsigned    const GAME_WIDTH  { 640 };
unsigned    const GAME_HEIGHT { 320 };


Entity::Entity(bool FRIENDLY)
    :xpos{0}, ypos{GAME_HEIGHT - 50}, 
    movementSpeed{20}, IS_FRIENDLY{FRIENDLY}, 
    hasCollided{false}, texture{}, sprite{}, boundingbox{sf::Vector2f(40.f,50.f)}
{
    if(!texture.loadFromFile("assets/0001.png"))
    {
        std::cout << "Could not load entity from texture" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));
    boundingbox.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));

    sprite.setPosition( xpos, ypos );
    boundingbox.setPosition( xpos, ypos );
    sprite.setScale(sf::Vector2f(-0.1f,0.1f));
    if ( !IS_FRIENDLY )
    {
        movementSpeed *= -1;
        xpos = GAME_WIDTH - 10;
        sprite.setScale(sf::Vector2f(0.1f,0.1f));
        //rekt.setFillColor( sf::Color::Red );
    }
}

void Entity::handleCollison(sf::Time const & frameDuration)
{
    xpos -= movementSpeed * frameDuration.asSeconds();
}

sf::Sprite Entity::render() const &
{
    return sprite;
}

bool Entity::collides( Entity* const other )
{
    // Check whether this collides with other
    return boundingbox.getGlobalBounds().intersects(
            ( other->boundingbox.getGlobalBounds() ) );
}


void Entity::updatePos(sf::Time const & frameDuration)
{
    xpos += movementSpeed * frameDuration.asSeconds();
    sprite.setPosition(xpos, ypos);
    boundingbox.setPosition(xpos, ypos);
}
