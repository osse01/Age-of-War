#ifndef TURRET_H
#define TURRET_H

#include "Dynamic.h"
#include "Projectile.h"

#include <SFML/Graphics.hpp>

class Turret : public Dynamic
{
public:
        // CONSTRUCTORS / DESTRUCTORS
        Turret(FileReader::Data&, bool, sf::Vector2f, 
               std::shared_ptr<sf::Time>);
        virtual ~Turret() = default;

        // FUNCTIONS
        void handleCollision(int, int) override;
        void updatePos()               override;
        void aim1(sf::Vector2f);
        void aim2(sf::Vector2f);
        std::shared_ptr<Projectile> spawnProjectile(FileReader::Data&,
                                                    std::shared_ptr<sf::Time>,
                                                    sf::Vector2f);

private:
    float angle;


};

#endif