#include "../include/Base.h"

Base::Base(FileReader::Data& data,  bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    : Entity::Entity(data, "Base",friendly, pos, frameDuration)
//  ---------------------------------------------
{

} 

std::shared_ptr<Projectile> Base::spawnProjectile(FileReader::Data& data,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f pos)
//  ---------------------------------------------
{
   std::shared_ptr<Projectile> projectile {};

   return projectile;
}

void Base::handleCollision(__attribute__((unused)) int, int otherDamage)
//  ---------------------------------------------
{
    takeDamage(otherDamage);
}

void Base::updatePos()
//  ---------------------------------------------
{

}

float Base::getRange()
//  ---------------------------------------------
{
    return 0.0f;
}

void Base::takeDamage(int otherDamage)
//  ---------------------------------------------
{
    Entity::hp -= otherDamage * frameDuration->asSeconds();
}

