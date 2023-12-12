#ifndef TURRET_H
#define TURRET_H

#include "Dynamic.h"
#include "Projectile.h"

#include <SFML/Graphics.hpp>

class Turret : public Dynamic
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    Turret(FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>, std::map<std::string, std::shared_ptr<sf::Sound>>);
    virtual ~Turret() = default;

    // FUNCTIONS
    void  handleCollision     (int, int)  override;
    void  updatePos           ()          override;
    float getcurrentCooldown  ();

    void  aim             (sf::Vector2f);
    void  changeSprite    ();
    void  updateCooldown  (std::shared_ptr<sf::Time>);  
    void  specialAttack   ();
    bool  inRange         (std::shared_ptr<Entity>) override;
    std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&,
                                                std::shared_ptr<sf::Time>,
                                                sf::Vector2f);
                                
    sf::Sprite& getSprite();

private:
    float   angle;
    float   g;
    const float   specialAttackCooldown;
    float   currentCooldown;
    float   initAngle;

    const float  SPECIAL_ATTACK_SPEED;
    float waitTime;
    bool movingUp;

    const static int IDLE { 0 };
    const static int SHOOT { 1 };
    const static int SPECIAL { 2 };

    std::map<std::string, std::shared_ptr<sf::Sound>> sound;
};

#endif