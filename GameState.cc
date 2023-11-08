#include "GameState.h"






void GameState::handleEvent(sf::Event event)
{

    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Space)
        {
            
        }
        break;

    default:
        break;

    }


}



void GameState::updateLogic     ()         
{
    
}

void GameState::renderFrame     ()  
{

}

int GameState::getNextState     ()       
{
    return nextState;
}