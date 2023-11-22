#ifndef ENEMY_H
#define ENEMY_H

#include <experimental/random>
#include <memory>
#include <SFML/Graphics.hpp>

class Enemy
{
    public:
        Enemy(std::shared_ptr<sf::Time>);
        ~Enemy() = default;

        std::vector<int> enemyPlay();

    private:
        std::vector<int> spawnAlgo();

        float delayCounter;
        float timeCounter;
        std::vector<int> spawnList;
        std::shared_ptr<sf::Time> frameDuration;



};


#endif