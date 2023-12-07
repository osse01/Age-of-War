#ifndef ENEMY_H
#define ENEMY_H

#include <experimental/random>
#include "FileReader.h"
#include <memory>
#include <SFML/Graphics.hpp>

class Enemy
{
    public:
        Enemy(FileReader::Data&, std::shared_ptr<sf::Time>);
        ~Enemy() = default;

        std::vector<int> enemyPlay();

    private:
        std::vector<int> spawnAlgo();
        void             updateTroop();

        int listSize;
        int waveSize;
        int waveLimit;
        int waveCounter;
        int delay; 
        int turretTime;
        int upgradeTime;

        float delayCounter;
        double totalTime;
        int lastTime;

        bool turret;
        bool HP;
        std::vector<int> spawnList;
        std::shared_ptr<sf::Time> frameDuration;

        FileReader::Data& data;


};


#endif