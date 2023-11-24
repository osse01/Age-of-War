#include "../include/Turret.h"


void Turret::handleCollision(__attribute__((unused)) int,
                             __attribute__((unused)) int)
{

}

void Turret::updatePos()
{

}

int  Turret::getType()
{
    return 0;
}

std::shared_ptr<Projectile> Turret::spawnProjectile(FileReader::Data& stats,
        sf::Vector2f enemyPos, std::shared_ptr<sf::Time> frameDuration)
{
    aim(enemyPos);
}

void Turret::aim(sf::Vector2f enemyPos)
{
    angle = 0;
}