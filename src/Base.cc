#include "../include/Base.h"

Base::Base(FileReader::Data& dataMap,  bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    : Entity::Entity(dataMap, "Base", friendly, pos, frameDuration), turret {nullptr},
    renderTexture {std::make_shared<sf::RenderTexture>()}, renderSprite {},
    turretPos {}, maxHp {dataMap.stats["Base"]["hp"]}, hpTexture {std::make_shared<sf::RenderTexture>()},
    spriteSpeed {dataMap.stats["Base"]["spriteSpeed"]}
{
    actionState = OPEN_GATE;
    Entity::rectSourceSprite.left = 512*23;

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
    turretPos.x = (isFriendly) ? turretPos.x : sprite.getGlobalBounds().width - turretPos.x;

    hpTexture->create(sprite.getGlobalBounds().width/50, sprite.getGlobalBounds().height/3);

}

sf::Sprite Base::setHpBar()
{
    // Set Position and Appearance for Initial Health Bar
    float outline {hpTexture->getSize().x/5};
    sf::RectangleShape hpBar {sf::Vector2f(hpTexture->getSize().x-2*outline,
                                            hpTexture->getSize().y-2*outline)};
    sf::RectangleShape currentHp {sf::Vector2f(hpTexture->getSize().x-2*outline,
                                            hpTexture->getSize().y-2*outline)};

    hpBar.setOrigin(0,0);
    hpBar.setPosition(outline,outline);
    hpBar.setOutlineThickness(outline);
    hpBar.setFillColor(sf::Color(109, 109, 110));
    hpBar.setOutlineColor(sf::Color(0, 0, 0));
    
    currentHp.setOrigin(0,0);
    currentHp.setPosition(outline, outline);
    currentHp.setOutlineThickness(outline);
    currentHp.setFillColor(sf::Color(200, 10, 0));
    currentHp.setOutlineColor(sf::Color(0, 0, 0));

    currentHp.setScale(sf::Vector2f(1, hp/maxHp));

    hpTexture->clear();

    hpTexture->draw(hpBar);
    hpTexture->draw(currentHp);

    sf::Sprite hpSprite {hpTexture->getTexture()};

    return hpSprite;
}

// Call Turrets spawnProjectile
std::shared_ptr<Projectile> Base::spawnProjectile(FileReader::Data& stats,
    std::shared_ptr<sf::Time> frameDuration, sf::Vector2f enemyPos)
{
    if (turret)
    {
        return turret->spawnProjectile(stats, frameDuration, enemyPos);
    }
    return nullptr;
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

// Call Turrets inRange
bool Base::inRange( std::shared_ptr<Entity> other )
{
    if (turret)
    {
       return turret->inRange(other); 
    }
    return false;
}

// Create Turret if None Exists
bool Base::buyTurret(FileReader::Data& stats, bool isFriendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
{
    if (turret)
    {
        return false;
    }

    turret = std::make_shared<Turret>(stats, isFriendly, sf::Vector2f( renderSprite.getGlobalBounds().left + turretPos.x,
                                                                      ypos - (sprite.getGlobalBounds().height - turretPos.y)), frameDuration);
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

    sf::Sprite hpBar {setHpBar()};
    float xPosHp = (isFriendly) ? renderTexture->getSize().x*0.65f : renderTexture->getSize().x*0.35f;
    hpBar.setPosition(xPosHp, renderTexture->getSize().y/10);

    renderTexture->draw(hpBar);
    
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
            if (Entity::rectSourceSprite.left == 13*512)
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