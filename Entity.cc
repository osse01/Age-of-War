#include <SFML/Graphics.hpp>
Entity::Entity(bool FRIENDLY)
    :xpos{0}, ypos{GAME_HEIGHT/2}, 
    IS_FRIENDLY{FRIENDLY}, MVMSPD{5}, 
    hasCollided{false},
    sf::RectangleShape rekt{10, 40}
{
    rekt.setFillCcolor(sf::Color::blue);
    rekt.setPosition(0, xpos, ypos);
}
Entity::render()
{
    window.draw(rekt)
}