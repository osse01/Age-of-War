#include "Melee.h"

Melee::Melee(const FileReader::Data& stats, bool friendly, sf::Vector2f pos)
 : Troop::Troop(stats, friendly, pos)
{}