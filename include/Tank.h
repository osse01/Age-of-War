#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include "Troop.h"


    class Tank : public Troop
    {
        public:
            Tank(FileReader::Data&, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
            virtual ~Tank() = default;

    };

#endif