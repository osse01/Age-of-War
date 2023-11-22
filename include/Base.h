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
    Base(const FileReader::Data&, bool , sf::Vector2f, std::shared_ptr<sf::Time>);
    ~Base() = default;

//FUNCTIONS
void    updateHp();
void    getBaseStats();

private:
sf::RectangleShape base;


};




#endif
