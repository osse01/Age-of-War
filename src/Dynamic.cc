#include "../include/Dynamic.h"


Dynamic::Dynamic( FileReader::Data& data, std::string troopType, 
                  bool friendly, sf::Vector2f pos, 
                  std::shared_ptr<sf::Time> frameDuration )
:
  // Data Member Initialization List
  //------------------------------------------------------------------
  Entity::Entity( data, troopType, friendly, pos, frameDuration ),

  DAMAGE        { data.stats[troopType]["damage"]                   },
  ATTACK_SPEED  { data.stats[troopType]["attackSpeed"]              },
  RANGE         { data.stats[troopType]["range"] * data.windowScale },
  DEATH_VALUE   { data.stats[troopType]["deathValue"]               }
  //------------------------------------------------------------------
{}

int Dynamic::getDamage()
// ---------------------------------------------
// Return the Dynamic object DAMAGE variable
{
    return DAMAGE;
}

int Dynamic::getDeathValue()
// ---------------------------------------------
// Return the Dynamic object DEATH_VALUE variable
{
    return DEATH_VALUE;
}

bool Dynamic::inRange( std::shared_ptr<Entity> other )
// ---------------------------------------------
// Checks if other entity is in range
{
  sf::FloatRect otherBounds { other->getBox().getGlobalBounds() };
  float minDistance {std::abs(otherBounds.left 
                          - (isFriendly ? boundingbox.getGlobalBounds().width
                                          : -otherBounds.width) 
                          - boundingbox.getGlobalBounds().left)};

    if (RANGE > minDistance)
    {
      return true;
    }
    return false;
}