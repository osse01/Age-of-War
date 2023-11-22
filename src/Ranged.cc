#include "../include/Ranged.h"

Ranged::Ranged(const FileReader::Data& stats, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
 : Troop::Troop(stats, friendly, pos, frameDuration)
{}

int Ranged::getType()
{
   return 2;
}