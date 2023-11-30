#include "../include/Turret.h"

#include <cmath>

Turret::Turret(FileReader::Data& data, bool isFriendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: Dynamic(data, "Turret", isFriendly, pos, frameDuration), angle { 30 }
{

}

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
    aim1(enemyPos);
}

void Turret::aim1(sf::Vector2f enemyPos)
{
    float projectileSpeed = 5;
    float g = 10;
    angle = atan(pow(projectileSpeed, 2) - sqrt(pow(projectileSpeed, 4) - g * (g * pow(enemyPos.x, 2) + 2*enemyPos.y * pow(projectileSpeed, 2))) / (g * enemyPos.x));
}

void Turret::aim2(sf::Vector2f enemyPos)
{
    float projectileSpeed = 5;
    float g = 10;
    angle = 1/2 * acos(((ypos-enemyPos.y)/2 - g/pow(projectileSpeed, 2) * pow(xpos-enemyPos.x, 2)) / sqrt(pow(xpos-enemyPos.x, 2)
     + pow(ypos-enemyPos.y, 2))) + 1/2 * atan((ypos-enemyPos.y) / (xpos-enemyPos.x));
}