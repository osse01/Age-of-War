#ifndef BASE_H
#define BASE_H

#include "Entity.h"

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
std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&, std::shared_ptr<sf::Time>, sf::Vector2f);
void    handleCollision(int, int) override;
void    updatePos()               override;
int     getDamage()               override;
int     getDeathValue() override;
float   getRange() override;
void    takeDamage(int);
//void updateHp();
//void getBaseStats();

private:
};




#endif
