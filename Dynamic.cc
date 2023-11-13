#include "Dynamic.h"


Dynamic::Dynamic(Melee::Stats stats)
    : Entity(stats.isFriendly, stats.xpos, stats.ypos, stats.hp, stats.sprite
             stats.boundingbox, stats.texturePath),
      MOVEMENTSPEED { stats.movementspeed }, DAMAGE { stats.damage }, DEATH_VALUE { stats.deathValue },
      BUY_VALUE { stats.buyValue }, RANGE { stats.range }
{}