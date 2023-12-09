#include "../include/Melee.h"

Melee::Melee(FileReader::Data& data, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
 : Troop::Troop(data, "Melee", friendly, pos, frameDuration)
{}