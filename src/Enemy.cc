#include "../include/Enemy.h"
#include <iostream>



Enemy::Enemy(std::shared_ptr<sf::Time> frameDuration)
:delayCounter{100}, timeCounter{0}, spawnList{}, frameDuration{frameDuration}
{
    // Create List with Troops 
    for(int i = 0; i < 10; i++)
    {
        spawnList.push_back(6);
    }
}

// Melee:6 Ranged:5 Tank:4 Turret:3
// Spawn Enemies after Certain Time
std::vector<int> Enemy::enemyPlay()
{
    std::vector<int> play{};
    if(delayCounter >= 100)
    {
        delayCounter = 0;
        return spawnAlgo();
    }
    delayCounter += std::experimental::randint(1,10)*(frameDuration->asSeconds());
    return play;
}

// Return Vector with Enemies
std::vector<int> Enemy::spawnAlgo()
{
    int tmp{std::experimental::randint(1,3)};
    std::vector<int> spawn{};
    timeCounter++;
    if(timeCounter == 5)
    {
        spawnList.erase(spawnList.begin());
        timeCounter = 0;
        spawnList.push_back(std::experimental::randint(4,6));

    }
    for(int i = 0; i <= tmp; i++)
    {
        spawn.push_back(spawnList.at(std::experimental::randint(0, static_cast<int>(spawnList.size()-1))));
    }
    return spawn;
}