#include "../include/Base.h"

Base::Base(const FileReader::Data& stats,  bool friendly, sf::Vector2f pos)
    : Entity::Entity(stats, friendly, pos)
{

} 

void Base::handleCollision(__attribute__((unused)) int, __attribute__((unused)) int)
{

}
void Base::updatePos()
{

}

int Base::getDamage()
{
    return 5;
}