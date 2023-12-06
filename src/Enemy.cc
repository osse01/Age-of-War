#include "../include/Enemy.h"
#include <iostream>



Enemy::Enemy(FileReader::Data& data, std::shared_ptr<sf::Time> frameDuration)
:listSize{data.stats["Enemy"]["listSize"]}, waveSize{data.stats["Enemy"]["waveSize"]}, waveLimit{data.stats["Enemy"]["waveLimit"]},
 waveCounter{0}, delay{data.stats["Enemy"]["timeDelay"]}, turretTime{data.stats["Enemy"]["turretTime"]}, 
 delayCounter{delay}, totalTime{}, lastTime{totalTime + 1}, turret{true}, HP{false}, spawnList{}, frameDuration{frameDuration}, data{data}
{
    for(int i = 0; i < listSize; i++)
    {
        spawnList.push_back(6);
    }
}


// Melee:6 Ranged:5 Tank:4 Turret:3
std::vector<int> Enemy::enemyPlay()
{
    totalTime += frameDuration->asSeconds();
    std::vector<int> play{};
    if(delayCounter >= delay)
    {
        delayCounter = 0;
        return spawnAlgo();
    }
    if(turret && (totalTime > turretTime))
    {
        play.push_back(3);
        turret = false;
    }
    if(totalTime / 15 > lastTime)
    {
        lastTime++;
        updateTroop();
    }
    delayCounter += std::experimental::randint(1,10)*(frameDuration->asSeconds());
    return play;
}

std::vector<int> Enemy::spawnAlgo()
{
    int tmp{std::experimental::randint(1,waveSize)};
    std::vector<int> spawn{};
    waveCounter++;
    if(waveCounter == waveLimit)
    {
        spawnList.erase(spawnList.begin());
        waveCounter = 0;
        spawnList.push_back(std::experimental::randint(4,6));

    }
    for(int i = 0; i <= tmp; i++)
    {
        spawn.push_back(spawnList.at(std::experimental::randint(0, static_cast<int>(spawnList.size()-1))));
    }
    return spawn;
}

void Enemy::updateTroop()
{
    std::string tmp {HP ? "hp" : "damage"};
    int value {HP ? 3 : 1};
    data.stats["Melee"][tmp] += value;
    data.stats["Ranged"][tmp] += value;
    data.stats["Tank"][tmp] += value;
    HP = !HP;
}