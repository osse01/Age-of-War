#include "../include/Base.h"

Base::Base(const FileReader::Data& stats,  bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    : Entity::Entity(stats, friendly, pos, frameDuration)
{

} 

std::shared_ptr<Projectile> Base::spawnProjectile(FileReader::Data& stats,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f pos)
{
   std::shared_ptr<Projectile> projectile {};

   return projectile;
}

void Base::handleCollision(__attribute__((unused)) int, int otherDamage)
{
    takeDamage(otherDamage);
}
void Base::updatePos()
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

float Base::getRange()
{
    return 0.0f;
}

void Base::takeDamage(int otherDamage)
{
    Entity::hp -= otherDamage * frameDuration->asSeconds();
}