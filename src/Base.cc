#include "../include/Base.h"

Base::Base(FileReader::Data& dataMap,  bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    : Entity::Entity(dataMap, "Base", friendly, pos, frameDuration), turret {nullptr},
    renderTexture {std::make_shared<sf::RenderTexture>()}, renderSprite {},
    turretPos {},
    spriteSpeed {dataMap.stats["Base"]["spriteSpeed"]}
{
    sprite.scale(dataMap.stats["Base"]["spriteScale"], dataMap.stats["Base"]["spriteScale"]);
    boundingbox.scale(dataMap.stats["Base"]["spriteScale"], dataMap.stats["Base"]["spriteScale"]);


    renderTexture->create(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    renderSprite.setTexture(renderTexture->getTexture());
    renderSprite.setOrigin(renderSprite.getGlobalBounds().width/2,renderSprite.getGlobalBounds().height);

    xpos += (isFriendly) ? renderSprite.getGlobalBounds().width/2
                           : -renderSprite.getGlobalBounds().width/2;
    renderSprite.setPosition(xpos, ypos);
    boundingbox.setPosition(xpos, ypos);

    turretPos = sf::Vector2f(sprite.getGlobalBounds().width * 0.78f, sprite.getGlobalBounds().height * 0.54f);
    turretPos.x *= (isFriendly) ? 1: -1;
} 

// Call Turrets spawnProjectile
std::shared_ptr<Projectile> Base::spawnProjectile(FileReader::Data& stats,
    std::shared_ptr<sf::Time> frameDuration, sf::Vector2f enemyPos)
{
    return turret->spawnProjectile(stats, frameDuration, enemyPos);
}

// Call takeDamage when Enemy Attacks
void Base::handleCollision(__attribute__((unused)) int, int otherDamage)
{
    takeDamage(otherDamage);
}

// Call Turrets updatePos
void Base::updatePos()
{
    if (turret)
    {
        turret->updatePos();
    }
}

// Call Turrets getRange
float Base::getRange()
{
    if (turret)
    {
       return turret->getRange(); 
    }
    return 0;
}

// Create Turret if None Exists
bool Base::buyTurret(FileReader::Data& stats, bool isFriendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
{
    if (turret)
    {
        return false;
    }
    turret = std::make_shared<Turret>(stats, isFriendly, sf::Vector2f(xpos + turretPos.x, ypos + turretPos.y), frameDuration);
    return true;
}


sf::Sprite & Base::getSprite() 
{
    changeSprite();

    renderTexture->clear(sf::Color(0,0,0,0));
    
    sprite.setPosition(renderTexture->getSize().x/2, renderTexture->getSize().y);
    renderTexture->draw(sprite);

    if (turret)
    {
        sf::Sprite turretSprite {turret->getSprite()};
                             turretSprite.setPosition(turretPos);
                             renderTexture->draw(turretSprite);
    }
    
    renderTexture->display();

    renderSprite.setTexture(renderTexture->getTexture());

    return renderSprite;
}

void Base::changeSprite()
{
    Entity::rectSourceSprite.top = actionState*256;

    spriteCounter += spriteSpeed;

    if ( spriteCounter * frameDuration->asSeconds() >= 3 )
    {
        if(Entity::rectSourceSprite.left == 0)
        {
            actionState = IDLE;
            Entity::rectSourceSprite.left = 512*23;
        }
        else
        {
            if (Entity::rectSourceSprite.left == 12*512)
            {
                actionState = IDLE;
            }
            Entity::rectSourceSprite.left -= 512;
        }

        Entity::sprite.setTextureRect(Entity::rectSourceSprite);
        spriteCounter = 0;
    }
}

void Base::takeDamage(int otherDamage)
// Remove HP when Enemy Attacks
// otherDamage is Zero when Enemy is not Attacking
{
    Entity::hp -= otherDamage;
}