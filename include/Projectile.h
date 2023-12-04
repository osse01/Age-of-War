#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "FileReader.h"
#include <memory>

class Projectile
{
    public:
    Projectile(FileReader::Data&, std::string, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
    virtual ~Projectile() = default;

    bool collides( sf::RectangleShape );
    void handleCollision();
    void updatePos();
    int  getDamage();
    bool  getIsFriendly();

    int     getDeathValue();
    float   getRange();

    bool isDead();

    sf::Sprite  getSprite       ()         const &;


    // VARIABLES
    private:
    const int           DAMAGE;
    const float         MOVEMENTSPEED;
    double              xpos;
    double              ypos;
    int                 hp;
    bool                isFriendly;
    bool                hasCollided;
    sf::Texture         texture;
    sf::Sprite          sprite;
    sf::RectangleShape  boundingbox;
    std::shared_ptr<sf::Time> frameDuration;

    const int g {10};
    float counter;
};

#endif