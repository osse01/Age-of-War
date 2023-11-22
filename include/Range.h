#ifndef RANGE_H
#define RANGE_H

#include <SFML/Graphics.hpp>
#include "Troop.h"


class Range : public Troop
{
    public:
    Range(const FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
    virtual ~Range() = default;
    int getType();

    //Projectile createProjectile(const FileReader::Data&, bool, sf::Vector2f) override;
};

#endif