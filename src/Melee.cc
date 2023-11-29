#include "../include/Melee.h"

Melee::Melee(const FileReader::Data& stats, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
 : Troop::Troop(stats, friendly, pos, frameDuration)
{}

std::shared_ptr<Projectile> Melee::spawnProjectile(FileReader::Data& stats,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f pos)
{
   std::shared_ptr<Projectile> projectile {};

   return projectile;
}