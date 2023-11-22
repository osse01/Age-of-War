#include "../include/Range.h"

Range::Range(const FileReader::Data& stats, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
 : Troop::Troop(stats, friendly, pos, frameDuration)
{}

/*Projectile Range::createProjectile(const FileReader::Data& stats, bool friendly, sf::Vector2f pos)
{
   Projectile shot {stats, friendly, pos};
   return shot;
}*/