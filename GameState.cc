#include "GameState.h"

GameState::GameState(int* curr)
: currentState{curr}
{
    nextState = GAME_STATE;
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
            nextState = MENU_STATE;
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

void GameState::renderFrame(sf::RenderWindow & window)  
{
    for(auto &it: friendlyQueue)
        {
            window.draw(it->render());
        }

    for(auto &it: enemyQueue)
        {
            window.draw(it->render());
        }
}

int GameState::getNextState()       
{
    return nextState;
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