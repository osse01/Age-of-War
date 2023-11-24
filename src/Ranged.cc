#include "../include/Ranged.h"

Ranged::Ranged(const FileReader::Data& stats, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
 : Troop::Troop(stats, friendly, pos, frameDuration)
{}

std::shared_ptr<Projectile> Ranged::spawnProjectile(FileReader::Data& stats,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f pos)
{
   std::shared_ptr<Projectile> projectile {};

   if ( (rectSourceSprite.left/128)%12 == 4)
   {
      pos = sf::Vector2f(xpos, ypos);
      stats.damage = DAMAGE;
      projectile = std::make_shared<Projectile> (stats, Entity::isFriendly, pos, frameDuration);
   }

   return projectile;
}