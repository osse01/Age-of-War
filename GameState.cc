#include "GameState.h"

#include <iostream> 

GameState::GameState(sf::RenderWindow * screen, int* curr, sf::Music* sound, sf::Time* frameDuration)
:   State(sound, frameDuration), friendlyQueue {}, enemyQueue {}, backgroundFile { "assets/background.jpeg" },
    window { screen }, backgroundTexture {}, backgroundSprite {},
    zoomFactor { sf::Vector2f( 0.9f, 0.6f ) }, currentState { curr }
{
    //  Load in Background Image
    if(!backgroundTexture.loadFromFile(backgroundFile))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in GameState::GameState().");
    }
    backgroundSprite.setTexture(backgroundTexture);
}

GameState::~GameState()
{
    for(auto &it: friendlyQueue)
        {
            delete it;
            it = nullptr;
        }
    for(auto &it: enemyQueue)
        {
            delete it;
            it = nullptr;
        }
    currentState = nullptr;
    frameDuration = nullptr;
}

void GameState::handleEvent(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Num1)
        {
            spawnFriendly();
        }
        if (event.key.code == sf::Keyboard::Num2)
        {
            spawnEnemy();
        }
        if (event.key.code == sf::Keyboard::M)
        {
            *currentState = MENU_STATE;
            music->stop();
        }
        if (event.key.code == sf::Keyboard::P)
        {
            *currentState = PAUSE_STATE;
            music->pause();
        }
        break;
    default:
        break;

    }
}

void GameState::updateLogic()         
{
    for(auto &it: friendlyQueue)
        {
            it->updatePos(*frameDuration);
        }
    for(auto &it: enemyQueue)
        {
            it->updatePos(*frameDuration);
        }

    handleCollisions();
}

void GameState::handleCollisions()
{
    // Handle Collision between Friendly and Enemy
    if (friendlyQueue.size() > 0 && enemyQueue.size() > 0)
    {
        if (friendlyQueue.at(0)->collides(enemyQueue.at(0)))
        {
            friendlyQueue.at(0) ->handleCollison(*frameDuration);
            enemyQueue.at(0)    ->handleCollison(*frameDuration);

        }
    }
    
    // Handle Collision between Enemies
    int behind{ 1 };
    for(int inFront{ 0 }; inFront < static_cast<int>(enemyQueue.size()) - 1; inFront++, behind++)
        { 
            if(enemyQueue.at(behind)->collides(enemyQueue.at(inFront)))
            {
                // Enemy Behind waits for Enemy in Front
                enemyQueue.at(behind)->handleCollison(*frameDuration);
            }
        }
    
    // Handle Collision between Friends
    behind = 1;
    for(int inFront{ 0 }; inFront < static_cast<int>(friendlyQueue.size()) - 1; inFront++, behind++)
        { 
            if(friendlyQueue.at(behind)->collides(friendlyQueue.at(inFront)))
            {
                // Friend Behind waits for Friend in Front
                friendlyQueue.at(behind)->handleCollison(*frameDuration);
            }
        }

}

void GameState::renderFrame()  
{
    //  Fix Background
    window->clear(sf::Color(255, 255, 255));

    backgroundSprite.setScale(zoomFactor*0.694422f);
    
    window->draw(backgroundSprite);
    
    //  Render units
    for(auto &it: friendlyQueue)
        {
            window->draw(it->render());
        }

    for(auto &it: enemyQueue)
        {
            window->draw(it->render());
        }
}

int GameState::getNextState()       
{
    return *currentState;
}

void GameState::spawnFriendly()
{
    Entity* friendly = new Entity{true};
    friendlyQueue.push_back(friendly);
}

void GameState::spawnEnemy()
{
    Entity* enemy = new Entity{false};
    enemyQueue.push_back(enemy);
}