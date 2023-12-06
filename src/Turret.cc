#include "../include/Turret.h"

#include <cmath>

Turret::Turret(FileReader::Data & data, bool isFriendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: Dynamic(data, "Turret", isFriendly, pos, frameDuration), angle { 30 }, counter {0}, g {1000}, r {0}
{

}

void Turret::handleCollision(__attribute__((unused)) int,
                             __attribute__((unused)) int)
{

}

void Turret::updatePos()
{
    sprite.setRotation(-angle);
}

std::shared_ptr<Projectile> Turret::spawnProjectile(FileReader::Data& dataMap,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f enemyPos)
{
    aim1(dataMap.stats["TurretProjectile"]["movementSpeed"], enemyPos);
    std::shared_ptr<Projectile> projectile {};
    if (counter == 300)
    {   counter = 0;
        projectile = std::make_shared<Projectile> (dataMap, "TurretProjectile", Entity::isFriendly, sf::Vector2f(xpos, ypos), angle, frameDuration);
    }
    counter++;
    return projectile;
}

sf::Sprite & Turret::getSprite()
{
    return sprite;
}

void Turret::aim1(int projectileSpeed, sf::Vector2f enemyPos)
{
    float x = enemyPos.x - xpos;
    float y = enemyPos.y - ypos;
    angle = 180/3.14 * atan(-y/x);
    angle += 23 * pow(x / 1200,1.15);
    if (!isFriendly)
    {
        x = -x;
        angle = 180 - angle;
    }
    
}

void Turret::aim2(int projectileSpeed, sf::Vector2f enemyPos)
{
    r = sqrt(pow(xpos-enemyPos.x, 2) + pow(ypos-enemyPos.y, 2));
    angle = 180/3.14 * (1/2 * acos(( g/pow(projectileSpeed, 2) * pow(xpos-enemyPos.x, 2) - (ypos - enemyPos.y)) / r) + 1/2 * atan((xpos-enemyPos.x) / r));
}