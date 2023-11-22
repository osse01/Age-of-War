#include "../include/Base.h"

Base::Base(const FileReader::Data& stats,  bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    : Entity::Entity(stats, friendly, pos, frameDuration)
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
    return 0;
}

int  Base::getType() 
{
    return 0;
}

int Base::getDeathValue()
{
    return 0;
}