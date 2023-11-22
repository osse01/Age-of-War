#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Dynamic.h"


class Projectile : public Dynamic
{
    public:
    Projectile(const FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
    virtual ~Projectile() = default;

    void handleCollision(int, int) override;
    int getType();
    void updatePos() ;

    private:
    const int g {10};
    float counter;
};

#endif