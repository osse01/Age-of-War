#include "../include/Troop.h"

#include <iostream>

Troop::Troop(FileReader::Data& data, std::string troopType, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: Dynamic::Dynamic(data, troopType, friendly, pos, frameDuration), troopState { 1 }, spriteCounter { 0 }, collisionCounter {0}, MOVEMENTSPEED { data.stats[troopType]["movementSpeed"] }
{}

void Troop::handleCollision(int nextTroopState, int otherDamage)
{   
    if (troopState != ATTACK)
    {
        troopState = nextTroopState;
    }
    
    collisionCounter = 0;

    if (Entity::isFriendly)    
    {
        Entity::xpos -= MOVEMENTSPEED * (frameDuration->asSeconds());
    }
    else
    {
        Entity::xpos += MOVEMENTSPEED * (frameDuration->asSeconds());
    }
    
    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);

    switch ( troopState ) {
        case IDLE:
            changeSprite();
            break;
        case ATTACK:
            changeSprite();
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
        Entity::xpos -= MOVEMENTSPEED * (frameDuration->asSeconds());
    }
    else
    {
        Entity::xpos += MOVEMENTSPEED * (frameDuration->asSeconds());
    }

    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);
    if ( collisionCounter >= 2*frameDuration->asSeconds() )
    {
        troopState = WALK;
        changeSprite();
    }
}

void Troop::changeSprite()
{
    float swapSprite {};

    switch (troopState)
    {
    case WALK:
        swapSprite = MOVEMENTSPEED;
        Entity::rectSourceSprite.top = WALK*128;
        break;
    case ATTACK:
        swapSprite = ATTACK_SPEED;
        Entity::rectSourceSprite.top = ATTACK*128;
        break;
    default:
        Entity::rectSourceSprite.top = IDLE*128;
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