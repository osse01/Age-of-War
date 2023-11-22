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
void handleCollision(int, int) override;
void updatePos()               override;
int  getDamage()               override;
//void updateHp();
//void getBaseStats();

private:


};




#endif
