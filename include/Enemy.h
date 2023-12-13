#ifndef ENEMY_H
#define ENEMY_H

#include "FileReader.h"

#include <SFML/Graphics.hpp>
#include <experimental/random>
#include <memory>
#include <iostream>

class Enemy
{
public:
    // CONSTRUCTORS // DESTRUCTORS
    Enemy( FileReader::Data&, std::shared_ptr<sf::Time> );
    ~Enemy() = default;

    // FUNCTIONS
    std::vector<int> enemyPlay   ();

private:
    // FUNCTIONS
    std::vector<int> spawnAlgo   ();
    void             updateTroop ();

    // VARIABLES
    int                         listSize;
    int                         waveSize;
    int                         waveLimit;
    int                         waveCounter;
    float                       delay; 
    float                       turretTime;
    float                       upgradeTime;

    float                       delayCounter;
    float                       totalTime;
    float                       lastTime;

    bool                        turret;
    bool                        HP;

    std::shared_ptr<sf::Time>   frameDuration;
    std::vector<int>            spawnList;
    FileReader::Data&           data;
};

#endif