#include <SFML/Graphics.hpp>
#include "Entity.h"


unsigned    const GAME_WIDTH  { 640 };
unsigned    const GAME_HEIGHT { 320 };


Entity::Entity(bool FRIENDLY)
    :xpos{0}, ypos{GAME_HEIGHT/2}, 
    movementSpeed{20}, IS_FRIENDLY{FRIENDLY}, 
    hasCollided{false},
    rekt{sf::Vector2f{10.f, 40.f}}
{
    rekt.setFillColor( sf::Color::Blue );
    rekt.setPosition( xpos, ypos );
    if ( !IS_FRIENDLY )
    {
        movementSpeed *= -1;
        xpos = GAME_WIDTH - 10;
        rekt.setFillColor( sf::Color::Red );
    }
}

void Entity::handleCollison(sf::Time const & frameDuration)
{
    xpos -= movementSpeed * frameDuration.asSeconds();
}

sf::RectangleShape Entity::render()
{
    return rekt;
}

bool Entity::collides( Entity* const other )
{
    // Check whether this collides with other
    return rekt.getGlobalBounds().intersects(
            ( other->render() ).getGlobalBounds() );
}


void Entity::updatePos(sf::Time const & frameDuration)
{
    xpos += movementSpeed * frameDuration.asSeconds();
    rekt.setPosition(xpos, ypos);
}
