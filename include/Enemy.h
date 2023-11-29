#ifndef ENEMY_H
#define ENEMY_H

#include <experimental/random>
#include <memory>
#include <SFML/Graphics.hpp>
#include "FileReader.h"

class Enemy
{
    public:
        Enemy(std::shared_ptr<sf::RenderWindow>, std::shared_ptr<sf::Time>);
        ~Enemy() = default;

        std::vector<int> enemyPlay();

    private:
        std::vector<int> spawnAlgo();

        float delayCounter;
        float spawnCounter;
        std::vector<int> spawnList;
        std::shared_ptr<sf::Time> frameDuration;
        FileReader::Enemy stats;


};


#endif