#include "../include/Dynamic.h"


Dynamic::Dynamic(const FileReader::Data& stats, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    : Entity::Entity(stats, friendly, pos, frameDuration),
      DAMAGE { stats.damage }, MOVEMENTSPEED { stats.movementSpeed }, RANGE { stats.range },
      ATTACK_SPEED { stats.attackSpeed }, DEATH_VALUE {/*fix later*/}, BUY_VALUE {/*fix later*/}
{}

int Dynamic::getDamage()
{
  return DAMAGE;
}