#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Dynamic.h"


class Projectile : public Dynamic
{
    public:
    Projectile(const FileReader::Data&, bool, sf::Vector2f);
    virtual ~Projectile() = default;

    void handleCollision(int, int);
    int getAttackSpeed(){return 0;};
    int getType(){return 4;};
    void kill();
    void updatePos() ;

    private:
    const int g {10};
    float counter;
};

#endif