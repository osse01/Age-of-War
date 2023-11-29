#ifndef MELEE_H
#define MELEE_H

#include <SFML/Graphics.hpp>
#include "Troop.h"


    class Melee : public Troop
    {
        public:
            Melee(const FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
            virtual ~Melee() = default;
            std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&, std::shared_ptr<sf::Time>, sf::Vector2f);
    };

#endif