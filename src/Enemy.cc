#include "../include/Enemy.h"
#include <iostream>



Enemy::Enemy(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Time> frameDuration)
:delayCounter{100}, spawnCounter{0}, spawnList{}, frameDuration{frameDuration}, stats {}
{
    FileReader reader{window};
    stats = reader.getEnemyData("Enemy", "assets/stage1.txt");
    for(int i = 0; i < stats.spawnListSize; i++)
    {
        spawnList.push_back(1);
    }
    
}

std::vector<int> Enemy::enemyPlay()
{
    std::vector<int> play{};
    if(delayCounter >= stats.delayCount)
    {
        delayCounter = 0;
        return spawnAlgo();
    }
    delayCounter += std::experimental::randint(1,10)*(frameDuration->asSeconds());
    return play;
}

std::vector<int> Enemy::spawnAlgo()
{
    int tmp{std::experimental::randint(1,stats.waveSize)};
    std::vector<int> spawn{};
    spawnCounter++;
    if(spawnCounter == stats.spawnCount)
    {
        spawnList.erase(spawnList.begin());
        spawnCounter = 0;
        spawnList.push_back(std::experimental::randint(1,3));

    }
    for(int i = 0; i <= tmp; i++)
    {
        spawn.push_back(spawnList.at(std::experimental::randint(0, static_cast<int>(spawnList.size()-1))));
    }
    return spawn;
}