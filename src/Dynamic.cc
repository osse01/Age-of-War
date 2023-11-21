#include "../include/Dynamic.h"


Dynamic::Dynamic(const FileReader::Data& stats, bool friendly, sf::Vector2f pos)
    : Entity::Entity(stats, friendly, pos),
      DAMAGE { stats.damage }, MOVEMENTSPEED { stats.movementSpeed }, RANGE { stats.range },
      ATTACK_SPEED { stats.attackSpeed }, DEATH_VALUE { stats.deathValue }, BUY_VALUE {/*fix later*/}
{}

int Dynamic::getDamage()
{
  return DAMAGE;
}

int Dynamic::getDeathValue()
//  ---------------------------------------------
//  Returns the Dynamic object DEATH_VALUE variable.
//  ---------------------------------------------
{
    return DEATH_VALUE;
}