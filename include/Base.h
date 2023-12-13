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
    // CONSTRUCTORS
    Base( FileReader::Data&,
          bool, sf::Vector2f,
          std::shared_ptr<sf::Time>);
    ~Base() = default;

    // FUNCTIONS
    std::shared_ptr<Projectile> spawnProjectile(
                        FileReader::Data&, 
                        std::shared_ptr<sf::Time>, 
                        sf::Vector2f)                   override;

    bool buyTurret  ( FileReader::Data&, bool,
                        std::shared_ptr<sf::Time>,
                        std::map<std::string,
                        std::shared_ptr<sf::Sound>>)    override;

    bool inRange    ( std::shared_ptr<Entity> other )   override;

    void    handleCollision     ( int, int )    override;
    void    updatePos           ()              override;
    void    specialAttack       ()              override;
    float   getCurrentCooldown  ()              override;

    sf::Sprite & getSprite      ()              override;

    void  takeDamage            ( int );

private:
    // FUNCTIONS
    sf::Sprite setHpBar();
    void changeSprite();

    // VARIABLES
    std::shared_ptr<sf::RenderTexture>  renderTexture;
    std::shared_ptr<sf::RenderTexture>  hpTexture;
    std::shared_ptr<Turret>             turret;
    sf::Vector2f                        turretPos;
    sf::Sprite                          renderSprite;

    const static int                    IDLE       { 0 };
    const static int                    OPEN_GATE  { 1 };

    float                               maxCooldown;
    float                               spriteSpeed;
    float                               maxHp;
};

#endif
