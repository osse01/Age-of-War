#ifndef RANGED_H
#define RANGED_H

#include <SFML/Graphics.hpp>
#include "Troop.h"


class Ranged : public Troop
{
    public:
    Ranged(const FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
    virtual ~Ranged() = default;
    int getType();

    //Projectile createProjectile(const FileReader::Data&, bool, sf::Vector2f) override;
};

#endif