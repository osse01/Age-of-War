#include "GameState.h"

#include <iostream> 

GameState::GameState(sf::RenderWindow * screen, int* curr, sf::Music* sound)
:   friendlyQueue {}, enemyQueue {}, backgroundFile { "assets/background.jpeg" }, treeFile { "assets/tree.png" },
    window { screen }, spriteImage { new sf::Image {} }, backgroundImage { new sf::Image {} },
    backgroundTexture { new sf::Texture {} }, treeTexture { new sf::Texture {} }, backgroundSprite { new sf::Sprite {} },
    treeSprite { new sf::Sprite {} }, zoomFactor { sf::Vector2f(0.9f, 0.6f) },  currentState { curr }, music { sound } 
{
    if(backgroundImage->loadFromFile(treeFile))
    {
        treeTexture->loadFromImage(*backgroundImage);
        treeSprite->setTexture(*treeTexture);
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find background image. Error in GameState::GameState().");
    }
    //  Load in Background Image
    if(spriteImage->loadFromFile(backgroundFile))
    {
        backgroundTexture->loadFromImage(*spriteImage);
        backgroundSprite->setTexture(*backgroundTexture);
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find background image. Error in GameState::GameState().");
    }

    //  Load in Tree

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

void GameState::updateLogic(sf::Time const & frameDuration)         
{
    for(auto &it: friendlyQueue)
        {
            it->updatePos(frameDuration);
        }
    for(auto &it: enemyQueue)
        {
            it->updatePos(frameDuration);
        }

    handleCollisions(frameDuration);
}

void GameState::handleCollisions(sf::Time const & frameDuration)
{
    // Handle Collision between Friendly and Enemy
    if (friendlyQueue.size() > 0 && enemyQueue.size() > 0)
    {
        if (friendlyQueue.at(0)->collides(enemyQueue.at(0)))
        {
            friendlyQueue.at(0) ->handleCollison(frameDuration);
            enemyQueue.at(0)    ->handleCollison(frameDuration);

        }
    }
    
    // Handle Collision between Enemies
    int behind{ 1 };
    for(int inFront{ 0 }; inFront < static_cast<int>(enemyQueue.size()) - 1; inFront++, behind++)
        { 
            if(enemyQueue.at(behind)->collides(enemyQueue.at(inFront)))
            {
                // Enemy Behind waits for Enemy in Front
                enemyQueue.at(behind)->handleCollison(frameDuration);
            }
        }
    
    // Handle Collision between Friends
    behind = 1;
    for(int inFront{ 0 }; inFront < static_cast<int>(friendlyQueue.size()) - 1; inFront++, behind++)
        { 
            if(friendlyQueue.at(behind)->collides(friendlyQueue.at(inFront)))
            {
                // Friend Behind waits for Friend in Front
                friendlyQueue.at(behind)->handleCollison(frameDuration);
            }
        }

}

void GameState::renderFrame()  
{
    //  Fix Background
    window->clear(sf::Color(255, 255, 255));

    backgroundSprite->setScale(zoomFactor*0.694422f);

    treeSprite->setOrigin(treeSprite->getLocalBounds().width / 2, treeSprite->getLocalBounds().height / 2);
    treeSprite->setPosition(window->getSize().x / 2, window->getSize().y / 1.25);
    treeSprite->setScale(zoomFactor*0.1f);

    
    window->draw(*backgroundSprite);
    window->draw(*treeSprite);
    
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