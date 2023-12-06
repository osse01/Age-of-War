#ifndef TURRET_H
#define TURRET_H

#include "Dynamic.h"
#include "Projectile.h"

#include <SFML/Graphics.hpp>

class Turret : public Dynamic
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    Turret(FileReader::Data&, bool, sf::Vector2f, 
           std::shared_ptr<sf::Time>);
    virtual ~Turret() = default;

    // FUNCTIONS
    void handleCollision(int, int) override;
    void updatePos()               override;
    void aim1(int, sf::Vector2f);
    void aim2(int, sf::Vector2f);
    std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&,
                                                std::shared_ptr<sf::Time>,
                                                sf::Vector2f);
                                
    sf::Sprite& getSprite();

private:
    float angle;
    int counter;
    float g;
    float r;


};

#endif