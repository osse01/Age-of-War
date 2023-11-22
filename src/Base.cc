#include "../include/Base.h"

Base::Base(const FileReader::Data& stats,  bool friendly, sf::Vector2f pos)
    : Entity::Entity(stats, friendly, pos)
{

} 

void Base::handleCollision(__attribute__((unused)) int, __attribute__((unused)) int, __attribute__((unused)) std::shared_ptr<sf::Time>)
{

}
void Base::updatePos(__attribute__((unused)) std::shared_ptr<sf::Time>)
{

}

int Base::getDamage()
{
    return 0;
}

int Base::getDeathValue()
{
    return 0;
}