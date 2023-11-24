#include "../include/Turret.h"


void Turret::handleCollision(__attribute__((unused)) int,
                             __attribute__((unused)) int)
{

}

void Turret::updatePos()
{

}

std::shared_ptr<Projectile> Turret::spawnProjectile(FileReader::Data& stats,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f enemyPos)
{
    aim(enemyPos);
}

void Turret::aim(sf::Vector2f enemyPos)
{
    angle = 0;
}