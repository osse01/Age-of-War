#include "../include/Enemy.h"
#include <iostream>



Enemy::Enemy(std::shared_ptr<sf::Time> frameDuration)
:delayCounter{100}, timeCounter{0}, spawnList{}, frameDuration{frameDuration}
{
    for(int i = 0; i < 10; i++)
    {
        spawnList.push_back(1);
    }
}

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

std::vector<int> Enemy::spawnAlgo()
{
    int tmp{std::experimental::randint(1,3)};
    std::vector<int> spawn{};
    timeCounter++;
    if(timeCounter == 5)
    {
        spawnList.erase(spawnList.begin());
        timeCounter = 0;
        spawnList.push_back(std::experimental::randint(1,3));

    }
    for(int i = 0; i <= tmp; i++)
    {
        spawn.push_back(spawnList.at(std::experimental::randint(0, static_cast<int>(spawnList.size()-1))));
    }
    return spawn;
}