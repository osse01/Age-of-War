#ifndef RANGED_H
#define RANGED_H

#include <SFML/Graphics.hpp>
#include "Troop.h"


class Ranged : public Troop
{
    public:
    Ranged(FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
    virtual ~Ranged() = default;
    std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&, std::shared_ptr<sf::Time>, sf::Vector2f);

    private:
    
};

#endif