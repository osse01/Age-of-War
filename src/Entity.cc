#include "../include/Entity.h"

Entity::Entity(FileReader::Data& data, std::string troopType, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    
:
    // Data Member Initialization List
    //------------------------------------------------------------------
    frameDuration       { frameDuration },
    boundingbox         { sf::Vector2f(data.boxSize[troopType].x, 
                          data.boxSize[troopType].y) },

    rectSourceSprite    { sf::Vector2i(0,0),data.spriteDim[troopType] },
    texture             {},

    sprite              { texture, rectSourceSprite   },
    hp                  { data.stats[troopType]["hp"] },

    xpos                { pos.x    },
    ypos                { pos.y    },
    isFriendly          { friendly },
    hasCollided         { false    },

    actionState         { 0 },
    spriteCounter       { 0 },
    audioNumber         { 1 }
    //------------------------------------------------------------------
{
    // Load Friendly or Enemy Image
    std::string friendOrFoe = (isFriendly) ? "friendly_" : "enemy_";
    if(!texture.loadFromFile("assets/" + friendOrFoe + data.files[troopType]))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in Entity::Entity().");
    }
    // Set Sprite Position
    sprite.setTextureRect(rectSourceSprite);

    float spriteBoxDiff {(sprite.getGlobalBounds().height-boundingbox.getGlobalBounds().height)/2};
    
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,boundingbox.getGlobalBounds().height + spriteBoxDiff));
    boundingbox.setOrigin(sf::Vector2f(boundingbox.getGlobalBounds().width/2,boundingbox.getGlobalBounds().height));

    sprite.setPosition( xpos, ypos );
    boundingbox.setPosition( xpos, ypos );
    boundingbox.setScale( data.windowScale, data.windowScale );

    // Mirror Friendly Sprite
    if(isFriendly)
    {
        sprite.setScale(sf::Vector2f(-data.windowScale,data.windowScale));
    }
    else
    {
        sprite.setScale(sf::Vector2f(data.windowScale,data.windowScale));
    }
}

bool Entity::collides( std::shared_ptr<Entity> other )
//  ---------------------------------------------
//  Checks if Unit has Collided and if we have lag.
//  ---------------------------------------------
{
    // Check whether this collides with other
    hasCollided = 
    boundingbox.getGlobalBounds().intersects(( other->boundingbox.getGlobalBounds()))
    || ( ((isFriendly ? 1 : -1)
       * (boundingbox.getGlobalBounds().left 
          - other->boundingbox.getGlobalBounds().left)) > 0 ) ;

    other->hasCollided = hasCollided;
    
    return hasCollided;
}

// Return Entity Sprite
sf::Sprite& Entity::getSprite()
{
    return sprite;
}

// Check if Entity is Dead
bool Entity::isDead()
{
    return hp <= 0;
}

// Return True if Friendly
bool Entity::getIsFriendly()
{
    return isFriendly;
}

// Return Entity Bounding Box
sf::RectangleShape Entity::getBox() 
{
    return boundingbox;
}

void Entity::playSound(std::map<std::string, std::shared_ptr<sf::Sound>> sound)
{
    if (rectSourceSprite.left%(12*128) == 4*128 && spriteCounter == 0)
    {

        sound["sword" + std::to_string(audioNumber)]->play();
        audioNumber = std::experimental::randint(1,3);
    }
    
}

// Return Entity HP
int Entity::getHP()
{
    return hp;
}

// Virtual Function for spawnProjectile 
std::shared_ptr<Projectile> Entity::spawnProjectile(
    __attribute__((unused)) FileReader::Data&,
    __attribute__((unused)) std::shared_ptr<sf::Time>,
    __attribute__((unused)) sf::Vector2f)
{
   std::shared_ptr<Projectile> projectile {};

   return projectile;
}