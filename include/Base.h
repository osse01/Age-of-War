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
    Base(const FileReader::Data&, bool , sf::Vector2f);
    ~Base() = default;

//FUNCTIONS
void handleCollision(int, int, std::shared_ptr<sf::Time>) override;
void updatePos(std::shared_ptr<sf::Time>)               override;
int  getDamage()               override;
int     getDeathValue() override;
//void updateHp();
//void getBaseStats();

private:


};




#endif
