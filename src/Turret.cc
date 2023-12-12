#include "../include/Turret.h"

#include <cmath>

Turret::Turret(FileReader::Data & data, bool isFriendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: Dynamic(data, "Turret", isFriendly, pos, frameDuration), angle { 30 },
  g {1000}, specialAttackCooldown { data.stats["Turret"]["cooldown"] }, currentCooldown { specialAttackCooldown },
   initAngle{angle}, SPECIAL_ATTACK_SPEED { data.stats["Turret"]["specialAttackSpeed"] }, waitTime {0.f}, movingUp {true}
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
    std::shared_ptr<Projectile> projectile {};
   
    switch (actionState)
    {
    case SPECIAL:
    {
        
        if (movingUp)
        {
            waitTime += frameDuration->asSeconds();
            if (waitTime > 0.3)
            {
                angle += (90 - initAngle)/8;
                waitTime = 0;
            }
            if (angle > 90)
            {
                angle = 90;
                movingUp = false;
            }
        }
        if (!movingUp)
        {
            if (angle < dataMap.stats["Turret"]["specialAngle"]) // kanske borde ändras??
            {
                actionState = SHOOT;
            } 
            if ( rectSourceSprite.left == 22*128 && spriteCounter == 0 )
            {
                projectile = std::make_shared<Projectile> (dataMap, "SpecialProjectile", Entity::isFriendly, sf::Vector2f(xpos, ypos), angle, frameDuration);
                angle -= 0.3;
            }  
        }
        
        
        break;
    }

    default:
    {
        actionState = SHOOT;
        aim(enemyPos);
        if ( rectSourceSprite.left == 22*128 && spriteCounter == 0 )
        {
            projectile = std::make_shared<Projectile> (dataMap, "TurretProjectile", Entity::isFriendly, sf::Vector2f(xpos, ypos), angle, frameDuration);
        }
        break;
    }
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
    float x = std::abs(enemyPos.x - xpos);
    float y = std::abs(enemyPos.y - ypos);
    
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
    case SPECIAL:
        swapSprite = SPECIAL_ATTACK_SPEED;
        if (movingUp)
        {
            swapSprite = 0;
            spriteCounter = 0;
            Entity::rectSourceSprite.left = 128*23;
            Entity::sprite.setTextureRect(Entity::rectSourceSprite);
        }
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
            actionState = (actionState == SPECIAL) ? SPECIAL : IDLE;
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


void Turret::specialAttack()
//  ---------------------------------------------
{
    if (currentCooldown == 0)
    {
        actionState = SPECIAL;
        waitTime = 0;
        movingUp = true;
        currentCooldown = specialAttackCooldown;
        initAngle= angle;
    }
}

void Turret::updateCooldown(std::shared_ptr<sf::Time> frameDuration)
//  ---------------------------------------------
//  Reduce currentCooldown.
//  ---------------------------------------------
{
    (currentCooldown <= 0) ? currentCooldown = 0 : currentCooldown -= frameDuration->asSeconds();
}

float Turret::getcurrentCooldown()
//  ---------------------------------------------
//  Return currentCooldown
//  ---------------------------------------------
{
    return currentCooldown;
}

bool Turret::inRange( std::shared_ptr<Entity> other )
// ---------------------------------------------
// Checks if other entity is in range
{
  sf::FloatRect otherBounds { other->getBox().getGlobalBounds() };
  float minDistance {std::abs(otherBounds.left 
                          - (isFriendly ? boundingbox.getGlobalBounds().width
                                          : -otherBounds.width) 
                          - boundingbox.getGlobalBounds().left)};

    if ((actionState == SPECIAL) ? INFINITY : RANGE > minDistance)
    {
      return true;
    }
    return false;
}