#include "../include/Dynamic.h"


Dynamic::Dynamic(FileReader::Data& data, std::string troopType, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
    : Entity::Entity(data, troopType, friendly, pos, frameDuration),
      DAMAGE { data.stats[troopType]["damage"] }, ATTACK_SPEED { data.stats[troopType]["attackSpeed"] },
      RANGE { data.stats[troopType]["range"] }, DEATH_VALUE { data.stats[troopType]["deathValue"] }
{}

float Dynamic::getDamage()
//  ---------------------------------------------
//  Returns the Dynamic object DAMAGE variable.
//  ---------------------------------------------
{
    return DAMAGE;
}

float Dynamic::getDeathValue()
//  ---------------------------------------------
//  Returns the Dynamic object DEATH_VALUE variable.
//  ---------------------------------------------
{
    return DEATH_VALUE;
}

float Dynamic::getRange()
//  ---------------------------------------------
//  Returns the Ranged object RANGE variable.
//  ---------------------------------------------
{
  return RANGE;
}