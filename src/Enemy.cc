#include "../include/Enemy.h"
#include <random> // Include the random library

Enemy::Enemy( FileReader::Data& data, std::shared_ptr<sf::Time> frameDuration )
: 
    // Data Member Initialization List
    //---------------------------------------------------------------------
    listSize        { static_cast<int>(data.stats["Enemy"]["listSize"])  },
    waveSize        { static_cast<int>(data.stats["Enemy"]["waveSize"])  },
    waveLimit       { static_cast<int>(data.stats["Enemy"]["waveLimit"]) },

    waveCounter     {0}, 

    delay           { data.stats["Enemy"]["timeDelay"]   },
    turretTime      { data.stats["Enemy"]["turretTime"]  },
    upgradeTime     { data.stats["Enemy"]["upgradeTime"] },

    delayCounter    { delay }, 
    totalTime       {},  
    lastTime        { totalTime + 1 }, 
    turret          { true }, 
    HP              { true }, 
    frameDuration   { frameDuration }, 
    spawnList       {},
    data            { data }
    //---------------------------------------------------------------------
{
    data.stats["Base"]["hp"] = data.stats["Enemy"]["enemyBaseHP"];

    // Create List with Troops
    for(int i = 0; i < listSize; i++)
    {
        spawnList.push_back(6);
    }
}

// Melee:6 Ranged:5 Tank:4 Turret:3
// Spawn Enemies after Certain Time
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
        turret = !turret;
    }
    if(totalTime / upgradeTime > lastTime)
    {
        lastTime++;
        updateTroop();
    }
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 10); // define the range
    delayCounter += distr(gen)*(frameDuration->asSeconds()); // generate numbers
    return play;
}

// Return Vector with Enemies
std::vector<int> Enemy::spawnAlgo()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, waveSize); // define the range
    int tmp{distr(gen)}; // generate numbers
    std::vector<int> spawn{};
    waveCounter++;
    if(waveCounter == waveLimit)
    {
        spawnList.erase(spawnList.begin());
        waveCounter = 0;
        std::uniform_int_distribution<> distr(4, 6); // define the range
        spawnList.push_back(distr(gen)); // generate numbers
    }
    for(int i = 0; i <= tmp; i++)
    {
        std::uniform_int_distribution<> distr(0, static_cast<int>(spawnList.size()-1)); // define the range
        spawn.push_back(spawnList.at(distr(gen))); // generate numbers
    }
    return spawn;
}

void Enemy::updateTroop()
{
    if (totalTime < 300)
    {
        std::string tmp {HP ? "hp" : "damage"};
        int value {HP ? 5 : 2};
        data.stats["Melee"][tmp] += value;
        data.stats["Ranged"][tmp] += value;
        data.stats["Tank"][tmp] += value;
        HP = !HP; 
    }
    
}
