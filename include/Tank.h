#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include "Troop.h"


    class Tank : public Troop
    {
        public:
            Tank(const FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
            virtual ~Tank() = default;
            std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&, std::shared_ptr<sf::Time>, sf::Vector2f);

    };

#endif