#include "GameState.h"
#include "Entity.h"




void GameState::handleEvent(sf::Event event)
{

    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Space)
        {
            spawnFriendly();
        }
        break;

    default:
        break;

    }


}



void GameState::updateLogic     ()         
{
    
}

void GameState::renderFrame     (sf::RenderWindow & window)  
{
    for(auto &it: friendlyQueue)
        {
            it->render();
        }
}

int GameState::getNextState     ()       
{
    return nextState;
}

void GameState::spawnFriendly()
{
    Entity* friendly = new Entity{true};
    friendlyQueue.push_back(friendly);
}