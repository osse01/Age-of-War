#include "../include/Troop.h"

#include <iostream>

const int WALK   { 0 };
const int IDLE   { 1 };
const int ATTACK { 2 };
const int TAKE_DAMAGE { 3 };

Troop::Troop(const FileReader::Data& stats, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: Dynamic::Dynamic(stats, friendly, pos, frameDuration), spriteCounter { 0 }, collisionCounter {0}
{}

void Troop::handleCollision(int troopState, int otherDamage)
{   
    collisionCounter = 0;

    if (Entity::isFriendly)    
    {
        Entity::xpos -= Dynamic::MOVEMENTSPEED * (frameDuration->asSeconds());
    }
    else
    {
        Entity::xpos += Dynamic::MOVEMENTSPEED * (frameDuration->asSeconds());
    }
    
    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);

    switch ( troopState ) {
        case IDLE:
            changeSprite(troopState);
            break;
        case ATTACK:
            changeSprite(troopState);
            takeDamage(otherDamage);
            break;
        case TAKE_DAMAGE:
            takeDamage(otherDamage);
            break;
        default:
            throw std::logic_error("    >>Error: The troopState does not exist!");
            break;
    }
}

void Troop::updatePos()
{
    collisionCounter += frameDuration->asSeconds();

    if (!Entity::isFriendly)    
    {
        Entity::xpos -= Dynamic::MOVEMENTSPEED * (frameDuration->asSeconds());
    }
    else
    {
        Entity::xpos += Dynamic::MOVEMENTSPEED * (frameDuration->asSeconds());
    }

    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);
    if ( collisionCounter >= 2*frameDuration->asSeconds() )
    {
        changeSprite(WALK);
    }
}

void Troop::changeSprite(int troopState)
{
    float swapSprite {};

    switch (troopState)
    {
    case WALK:
        swapSprite = MOVEMENTSPEED;
        Entity::rectSourceSprite.top = 0;
        break;
    case ATTACK:
        swapSprite = ATTACK_SPEED;
        Entity::rectSourceSprite.top = 256;
        break;
    default:
        Entity::rectSourceSprite.top = 128;
        swapSprite = 100;
        break;
    }

    spriteCounter += swapSprite;

    if ( spriteCounter * frameDuration->asSeconds() >= 3 )
    {
        if(Entity::rectSourceSprite.left == 128*23)
        {
            Entity::rectSourceSprite.left = 0;
        }
        else
        {
            Entity::rectSourceSprite.left += 128;
        }

        Entity::sprite.setTextureRect(Entity::rectSourceSprite);
        spriteCounter = 0;
    }
}

void Troop::takeDamage(int otherDamage)
{
        Entity::hp -= otherDamage;
}

int Troop::getDamage()
{
    int damage {};
    if ( (rectSourceSprite.left)%(12*128) == 4*128 && spriteCounter == 0 )
    {
        damage = DAMAGE;
    }
    return damage;
}

std::shared_ptr<Projectile> Troop::spawnProjectile(FileReader::Data& stats,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f pos)
{
   std::shared_ptr<Projectile> projectile {};

   return projectile;
}