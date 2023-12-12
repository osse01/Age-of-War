#include "../include/Ranged.h"

Ranged::Ranged(FileReader::Data& data, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
 : Troop::Troop(data, "Ranged", friendly, pos, frameDuration)
{}

// Spawn and Return Ranged Projectile
std::shared_ptr<Projectile> Ranged::spawnProjectile(FileReader::Data& data,
                                                    std::shared_ptr<sf::Time> frameDuration,
                                                    sf::Vector2f pos)
{
   std::shared_ptr<Projectile> projectile {};
   int angle { 0 };
   if ( actionState == IDLE )
   {
      actionState = ATTACK;
   }

   if ( (rectSourceSprite.left)%(12*128) == 4*128 && spriteCounter == 0 )
   {
      // Set Projectile Position
      int tmp {isFriendly ? 1 : -1};
      pos = sf::Vector2f(xpos + tmp * sprite.getGlobalBounds().width/2, ypos - boundingbox.getGlobalBounds().height/2);
      projectile = std::make_shared<Projectile> (data, "RangedProjectile", Entity::isFriendly, pos, angle, frameDuration);
   }

   return projectile;
}