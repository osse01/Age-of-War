#include "../include/Ranged.h"

Ranged::Ranged(FileReader::Data& data, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
 : Troop::Troop(data, "Ranged", friendly, pos, frameDuration)
{}

std::shared_ptr<Projectile> Ranged::spawnProjectile(FileReader::Data& data,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f pos)
{
   std::shared_ptr<Projectile> projectile {};

   if ( troopState == IDLE )
   {
      troopState = ATTACK;
   }

   if ( (rectSourceSprite.left)%(12*128) == 4*128 && spriteCounter == 0 )
   {
      pos = sf::Vector2f(xpos, ypos);
      projectile = std::make_shared<Projectile> (data, "RangedProjectile", Entity::isFriendly, pos, frameDuration);
   }

   return projectile;
}