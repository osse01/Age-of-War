#include <SFML/Graphics.hpp>
#include "Entity.h"


unsigned    const GAME_WIDTH  { 640 };
unsigned    const GAME_HEIGHT { 320 };


Entity::Entity(bool FRIENDLY)
    :xpos{0}, ypos{GAME_HEIGHT/2}, 
    IS_FRIENDLY{FRIENDLY}, MVMSPD{5}, 
    hasCollided{false},
    sf::RectangleShape rekt{10, 40}
{
    rekt.setFillCcolor(sf::Color::blue);
    rekt.setPosition(0, xpos, ypos);
}

void Entity::render()
{
    window.draw(rekt)
}

void Entity::updatePos()
{
    if (rekt.getPosition() >= GAME_WIDTH)
    {
        xpos = 0;
    }
    xpos += MVMSPD;
}