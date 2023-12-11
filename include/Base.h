#ifndef BASE_H
#define BASE_H

#include "Entity.h"
#include "Turret.h"

#include <SFML/Graphics.hpp>


class Base : public Entity
//  =============   Base CLASS    ===============
//  This Class Handles ...
{
public:
//CONSTRUCTORS
    Base(FileReader::Data&, bool , sf::Vector2f, std::shared_ptr<sf::Time>);
    ~Base() = default;

//FUNCTIONS
std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&, std::shared_ptr<sf::Time>, sf::Vector2f) override;
void handleCollision(int, int) override;
void updatePos()               override;

sf::Sprite & getSprite()       override;
bool        inRange( std::shared_ptr<Entity> other )        override;

void  takeDamage(int);
bool  buyTurret(FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>) override;
//void updateHp();
//void getBaseStats();

private:
sf::Sprite setHpBar();
void changeSprite();

std::shared_ptr<Turret> turret;
std::shared_ptr<sf::RenderTexture> renderTexture;
sf::Sprite renderSprite;
sf::Vector2f turretPos;

float maxHp;

std::shared_ptr<sf::RenderTexture> hpTexture;

float spriteSpeed;

const static int IDLE { 0 };
const static int OPEN_GATE { 1 };

};




#endif
