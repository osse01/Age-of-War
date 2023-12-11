#include "../include/Base.h"

Base::Base(FileReader::Data& dataMap,  bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    : Entity::Entity(dataMap, "Base", friendly, pos, frameDuration), turret {nullptr},
    renderTexture {std::make_shared<sf::RenderTexture>()}, renderSprite {}
{
    renderTexture->create(texture.getSize().x, texture.getSize().y);
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
        turret->updateCooldown(frameDuration);
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
    turret = std::make_shared<Turret>(stats, isFriendly, sf::Vector2f(pos.x, pos.y - 200), frameDuration);
    return true;
}


sf::Sprite & Base::getSprite() 
{
    renderTexture->clear(sf::Color(0,0,0,0));
    if (!turret)
    {
        return sprite;
    }
    
    sprite.setPosition(texture.getSize().x/2, texture.getSize().y/2);
    renderTexture->draw(sprite);

    sf::Sprite turretSprite {turret->getSprite()};
    int tmp{isFriendly ? 1 : -1};
    turretSprite.setPosition(sprite.getPosition().x + tmp * sprite.getGlobalBounds().width/2,
                             sprite.getPosition().y - 100);
    renderTexture->draw(turretSprite);
    renderTexture->display();

    renderSprite.setTexture(renderTexture->getTexture());
    renderSprite.setOrigin(renderSprite.getGlobalBounds().width/2, renderSprite.getGlobalBounds().height/2);
    renderSprite.setPosition(xpos, ypos);

    return renderSprite;
}

void Base::takeDamage(int otherDamage)
// Remove HP when Enemy Attacks
// otherDamage is Zero when Enemy is not Attacking
{
    Entity::hp -= otherDamage;
}

void Base::specialAttack()
//  ---------------------------------------------
//  If we have a Turret, Call the Turrets special attack!!
//  and then Return true or false.
//  ---------------------------------------------
{
    if ( turret && turret->getcurrentCooldown() == 0 )
    {
        turret->specialAttack();
    }
}

float Base::getCooldown()
//  ---------------------------------------------
//  Return Cooldown of Turret Special Ability
//  ---------------------------------------------
{
    return (turret) ? turret->getcurrentCooldown() : 0;
}