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
    void    handleCollision (int, int)  override;
    void    updatePos       ()          override;
    float   getRange        ()          override;
    void    takeDamage      (int);
    bool    buyTurret       (FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>) override;

    std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&, std::shared_ptr<sf::Time>, sf::Vector2f) override;
    std::vector<std::shared_ptr<Projectile>> special(FileReader::Data&, std::shared_ptr<sf::Time>, sf::Vector2f, float) override;


    sf::Sprite & getSprite()  override;

    //void updateHp();
    //void getBaseStats();

private:
std::shared_ptr<Turret> turret;
std::shared_ptr<sf::RenderTexture> renderTexture;
sf::Sprite renderSprite;
};




#endif
