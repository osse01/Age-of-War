#ifndef MELEE_H
#define MELEE_H

#include <SFML/Graphics.hpp>
#include "Troop.h"


    class Melee : public Troop
    {
        public:
            Melee(const FileReader::Data&, bool, sf::Vector2f);
            virtual ~Melee() = default;
    };

#endif