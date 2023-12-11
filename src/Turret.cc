#include "../include/Turret.h"

#include <cmath>

Turret::Turret(FileReader::Data & data, bool isFriendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: Dynamic(data, "Turret", isFriendly, pos, frameDuration), angle { 30 }, g {1000}, r {0}, spriteCounter {}, actionState { IDLE }
{
    sprite.setOrigin(data.stats["Turret"]["originX"], data.stats["Turret"]["originY"]);
}

void Turret::handleCollision(__attribute__((unused)) int,
                             __attribute__((unused)) int)
{}

// Update Turret Position Depending on Friendly or Enemy
void Turret::updatePos()
{
    int tmp = isFriendly ? -1 : 1;
    sprite.setRotation( angle * tmp );
    changeSprite();
}

// Spawn and Return Turret Projectile
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

// Return Turret Sprite
sf::Sprite & Turret::getSprite()
{
    return sprite;
}

// Aim towards Enemy
void Turret::aim(sf::Vector2f enemyPos)
{
    actionState = SHOOT;
    float x = abs(enemyPos.x - xpos);
    float y = enemyPos.y - ypos;
    
    angle = 180/3.14 * atan(-y/x);
    angle += 23 * pow(x / 1200,1.15);
}

// Change Turret Sprite
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

    // Change to next Sprite in Sprite Sheet
    if ( spriteCounter * frameDuration->asSeconds() >= 3 )
    {
        if(Entity::rectSourceSprite.left == 0)
        {
            // Set to Idle to Finish Animation
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