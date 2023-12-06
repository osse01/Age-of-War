#ifndef TURRET_H
#define TURRET_H

#include "Dynamic.h"
#include "Projectile.h"

#include <SFML/Graphics.hpp>

class Turret : public Dynamic
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    Turret(FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
    virtual ~Turret() = default;

    // FUNCTIONS
    void  handleCollision  (int, int)  override;
    void  updatePos        ()          override;
    void  specialAttack    (FileReader::Data&, std::shared_ptr<sf::Time>)  override;

    void aim1(int, sf::Vector2f);
    void changeSprite();
    void aim2(int, sf::Vector2f);
    std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&,
                                                std::shared_ptr<sf::Time>,
                                                sf::Vector2f);
                                
    sf::Sprite& getSprite();
private:
    float angle;
    float g;
    float r;
    int   spriteCounter;
    int   actionState;

    const static int IDLE { 0 };
    const static int SHOOT { 1 };
};

#endif