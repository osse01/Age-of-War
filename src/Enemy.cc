#include "../include/Enemy.h"



Enemy::Enemy(std::shared_ptr<sf::Time> frameDuration)
:delayCounter{144}, timeCounter{0}, spawnList{}, frameDuration{frameDuration}
{
    for(int i = 0; i < 10; i++)
    {
        spawnList.push_back(1);
    }
}

int Enemy::enemyPlay()
{
    if(delayCounter >= 144)
    {
        delayCounter = 0;
        return spawnAlgo();
    }
    delayCounter += std::experimental::randint(1,3);
    return 0;
}

int Enemy::spawnAlgo()
{
    timeCounter++;
    if(timeCounter == 3)
    {
        spawnList.erase(spawnList.begin());
        timeCounter = 0;
        spawnList.push_back(std::experimental::randint(1,3));

    }
    return spawnList.at(std::experimental::randint(0, static_cast<int>(spawnList.size()-1)));
}