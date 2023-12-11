#include "../include/Turret.h"

#include <cmath>

Turret::Turret(FileReader::Data & data, bool isFriendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: Dynamic(data, "Turret", isFriendly, pos, frameDuration), angle { 30 }, g {1000}
{
    sprite.setOrigin(data.stats["Turret"]["originX"], data.stats["Turret"]["originY"]);
}

void Turret::handleCollision(__attribute__((unused)) int,
                             __attribute__((unused)) int)
{}

void Turret::updatePos()
{
    sprite.setRotation(-angle);
    changeSprite();
}

std::shared_ptr<Projectile> Turret::spawnProjectile(FileReader::Data& dataMap,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f enemyPos)
{
    aim(enemyPos);
    std::shared_ptr<Projectile> projectile {};
    if ( rectSourceSprite.left == 22*128 && spriteCounter == 0 )
   {
      projectile = std::make_shared<Projectile> (dataMap, "TurretProjectile", Entity::isFriendly, sf::Vector2f(xpos, ypos), angle, frameDuration);
   }

    return projectile;
}

sf::Sprite & Turret::getSprite()
{
    return sprite;
}

void Turret::aim(sf::Vector2f enemyPos)
{
    actionState = SHOOT;
    float x = enemyPos.x - xpos;
    float y = enemyPos.y - ypos;
    angle = 180/3.14 * atan(-y/x);
    angle += 23 * pow(std::abs(x) / 1200,1.15);
    if (!isFriendly)
    {
        x = -x;
        angle = 180 - angle;
    }
    // float v = projectileSpeed;
// 
    // float root = v*v*v*v - g*g*x*x - 2*g*y*v*v; 
    // std::cout << x << std::endl;
    // std::cout << y << std::endl;
    // angle = 180/3.14 * ( (atan(v*v + sqrt(root)) / (g*x)) );
    
}

void Turret::changeSprite()
{
    float swapSprite {};

    switch (actionState)
    {
    case SHOOT:
        swapSprite = ATTACK_SPEED;
        break;
    default:
        swapSprite = 0;
        break;
    }

    spriteCounter += swapSprite;

    if ( spriteCounter * frameDuration->asSeconds() >= 3 )
    {
        if(Entity::rectSourceSprite.left == 0)
        {
            actionState = IDLE;
            Entity::rectSourceSprite.left = 128*23;
        }
        else
        {
            Entity::rectSourceSprite.left -= 128;
        }

        Entity::sprite.setTextureRect(Entity::rectSourceSprite);
        spriteCounter = 0;
    }
}