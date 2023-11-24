#ifndef TURRET_H
#define TURRET_H

#include "Dynamic.h"
#include "Projectile.h"

#include <SFML/Graphics.hpp>

class Turret : public Dynamic
{
public:
        // CONSTRUCTORS / DESTRUCTORS
        Turret(const FileReader::Data&, bool, sf::Vector2f, 
               std::shared_ptr<sf::Time>);
        virtual ~Turret() = default;

        // FUNCTIONS
        void handleCollision(int, int) override;
        void updatePos()               override;
        int  getType()                 override;
        void aim(sf::Vector2f);
        std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&,
        sf::Vector2f, std::shared_ptr<sf::Time>);

private:
    float angle;


};

#endif