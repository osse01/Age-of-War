#include "Troop.h"

#include <iostream>

Troop::Troop(const FileReader::Data& stats, bool friendly, sf::Vector2f pos)
: Dynamic::Dynamic(stats, friendly, pos)
{}

void Troop::handleCollision(int troopState)
{   
    if (Entity::isFriendly)    
    {
        Entity::xpos -= Dynamic::MOVEMENTSPEED;
    }
    else
    {
        Entity::xpos += Dynamic::MOVEMENTSPEED;
    }
    
    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);

    switch ( troopState ) {
        case 0:
            idle();
            break;
        case 1:
            attack();
            break;
        default:
            throw std::logic_error("    >>Error: The troopState does not exist!");
    }
}

void Troop::updatePos()
{
    if (!Entity::isFriendly)    
    {
        Entity::xpos -= Dynamic::MOVEMENTSPEED;
    }
    else
    {
        Entity::xpos += Dynamic::MOVEMENTSPEED;
    }

    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);
    walk();
}

void Troop::changeSprite()
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
}

void Troop::walk()
{
    Entity::rectSourceSprite.top = 0;
    changeSprite();
}

void Troop::idle()
{
    Entity::rectSourceSprite.top = 128;
    changeSprite();
}

void Troop::attack()
{
    Entity::rectSourceSprite.top = 256;
    changeSprite();
}