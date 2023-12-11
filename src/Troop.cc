#include "../include/Troop.h"

#include <iostream>

Troop::Troop(FileReader::Data& data, std::string troopType, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: Dynamic::Dynamic(data, troopType, friendly, pos, frameDuration), collisionCounter {0},
  MOVEMENTSPEED { data.stats[troopType]["movementSpeed"] * data.windowScale }
{}

void Troop::handleCollision(int nextTroopState, int otherDamage)
{   
    if (actionState != ATTACK)
    {
        actionState = nextTroopState;
    }
    
    collisionCounter = 0;

    // Move Back Troop after Collision
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

    
    switch ( actionState ) {
        // Call changeSprite if Idle
        case IDLE:
            changeSprite();
            break;
        // Call changeSprite and takeDamage if Attacking
        case ATTACK:
            changeSprite();
            takeDamage(otherDamage);
            break;
        // Call takeDamage if Enemy is Attacking
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
    // Update Troop Position
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
        actionState = WALK;
        changeSprite();
    }
}

// Change to next Sprite
void Troop::changeSprite()
{
    float swapSprite {};

    switch (actionState)
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
        // Set Sprite to first Sprite in Sprite Sheet
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

// Decrease HP from Enemy Damage
void Troop::takeDamage(int otherDamage)
{
        Entity::hp -= otherDamage;
}

// Return Troop Damage 
int Troop::getDamage()
{
    int damage {};
    if ( (rectSourceSprite.left)%(12*128) == 4*128 && spriteCounter == 0 )
    {
        damage = DAMAGE;
    }
    return damage;
}