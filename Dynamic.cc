#include "Dynamic.h"


Dynamic::Dynamic(const FileReader::Data& stats, bool friendly, sf::Vector2f pos)
    : Entity::Entity(stats, friendly, pos),
      MOVEMENTSPEED { stats.movementSpeed }, DAMAGE { stats.damage }, DEATH_VALUE {/* fix later*/},
      BUY_VALUE {/*fix later*/}, RANGE { /*fix later*/ }
{}