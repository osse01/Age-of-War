#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "FileReader.h"
#include <memory>

class Projectile
{
    public:
    Projectile(FileReader::Data&, std::string, bool, sf::Vector2f, float, std::shared_ptr<sf::Time>);
    virtual ~Projectile() = default;

    bool collides( sf::RectangleShape );
    void handleCollision();
    void updatePos();
    int  getDamage();
    bool  getIsFriendly();
    bool isDead();

    sf::Sprite & getSprite();


    // VARIABLES
    private:
    const float         DAMAGE;
    const float         MOVEMENTSPEED;
    const float         INITIAL_ANGLE;
    float               xpos;
    float               ypos;
    float               dx;
    float               dy;
    float               x0;
    float               y0;
    float               hp;
    bool                isFriendly;
    bool                hasCollided;
    float               elapsedTime;
    sf::Texture         texture;
    sf::Sprite          sprite;
    sf::RectangleShape  boundingbox;
    std::shared_ptr<sf::Time> frameDuration;

    const int g {1000};
};

#endif