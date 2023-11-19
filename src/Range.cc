#include "../include/Range.h"

Range::Range(const FileReader::Data& stats, bool friendly, sf::Vector2f pos)
 : Troop::Troop(stats, friendly, pos)
{}

/*Projectile Range::createProjectile(const FileReader::Data& stats, bool friendly, sf::Vector2f pos)
{
   Projectile shot {stats, friendly, pos};
   return shot;
}*/