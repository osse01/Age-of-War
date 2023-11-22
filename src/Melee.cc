#include "../include/Melee.h"

Melee::Melee(const FileReader::Data& stats, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
 : Troop::Troop(stats, friendly, pos, frameDuration)
{}

int Melee::getType()
{
    return 1;
}