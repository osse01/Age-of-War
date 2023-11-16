#include "GameState.h"

#include <iostream>
#include "utility"

GameState::GameState(sf::RenderWindow* screen,  sf::Music* sound, sf::Time* frameDuration)
:   melee {}, ranged {}, tank {}, State(sound, frameDuration), friendlyQueue {}, enemyQueue {},
    backgroundFile { "assets/background.jpeg" }, window { screen }, backgroundTexture {},
    backgroundSprite {}, zoomFactor { sf::Vector2f( 0.9f, 0.6f ) }, nextstate { GAME_STATE }, stage { 1 }, gui { 1, screen }
{
    window->setFramerateLimit(18);

    //  Load in Background Image
    if(!backgroundTexture.loadFromFile(backgroundFile))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in GameState::GameState().");
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(window->getSize().x / backgroundSprite.getGlobalBounds().width, window->getSize().y / backgroundSprite.getGlobalBounds().height);

    FileReader reader {};
    melee = reader.returnData("Melee", "assets/stage1.txt");
}

GameState::~GameState()
{
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
            nextstate = MENU_STATE;
            music->stop();
        }
        if (event.key.code == sf::Keyboard::P)
        {
            nextstate = PAUSE_STATE;
            music->pause();
        }
        break;

    case sf::Event::MouseButtonPressed:
    {
        sf::Event::MouseButtonEvent mouse { event.mouseButton };
        if (mouse.button == sf::Mouse::Button::Left)
        {
            switch (gui.buttonClicked(GAME_STATE, mouse.x, mouse.y))
            {
                case 6:
                    spawnFriendly();
                    break;
                case 5:
                    spawnEnemy();
                    break;
                case 1:
                    window->close();
                    break;
                default:
                    break;
            }
        }
        break;
    }
    default:
        break;

    }
}

void GameState::updateLogic()         
{
    std::vector<int> deadEntitiesFriendly{};
    std::vector<int> deadEntitiesEnemy{};
    int i {};
    for(auto &it: friendlyQueue)
        {
            if ( it->isDead() )
            {
                deadEntitiesFriendly.push_back(i);
            }
            it->updatePos();
            i++;
        }
    i = 0;
    for(auto &it: enemyQueue)
        {
            if ( it->isDead() )
            {
                deadEntitiesEnemy.push_back(i);
            }
            it->updatePos();
            i++;
        }
    for (int j: deadEntitiesFriendly)
    {
        friendlyQueue.erase( friendlyQueue.begin() + j );
    }
    for (int j: deadEntitiesEnemy)
    {
        enemyQueue.erase( enemyQueue.begin() + j );
    }
    handleCollisions();
}

void GameState::handleCollisions()
{
    // Handle Collision between Friendly and Enemy
    if ( friendlyQueue.size() > 0 && enemyQueue.size() > 0 )
    {
        if ( friendlyQueue.at(0)->collides(  enemyQueue.at(0) ) )
        {
            friendlyQueue.at(0) ->handleCollision(1, enemyQueue.at(0)->getDamage());
            enemyQueue.at(0)    ->handleCollision(1, friendlyQueue.at(0)->getDamage());
        }
    }
    
    // Handle Collision between Enemies
    int behind{ 1 };
    for(int inFront{ 0 }; inFront < static_cast<int>(enemyQueue.size()) - 1; inFront++, behind++)
        { 
            if( enemyQueue.at(behind)->collides( enemyQueue.at(inFront) ) )
            {
                // Enemy Behind waits for Enemy in Front
                enemyQueue.at(behind)->handleCollision(0, 0);
            }
        }
    
    // Handle Collision between Friends
    behind = 1;
    for( int inFront{ 0 }; inFront < static_cast<int>(friendlyQueue.size()) - 1; inFront++, behind++ )
        { 
            if( friendlyQueue.at(behind)->collides( friendlyQueue.at(inFront) ) )
            {
                // Friend Behind waits for Friend in Front
                friendlyQueue.at(behind)->handleCollision(0, 0);
            }
        }

}

void GameState::renderFrame()  
{

    //  Fix Background
    window->clear(sf::Color(255, 255, 255));

    //backgroundSprite.setScale(zoomFactor*0.694422f);
    
    window->draw(backgroundSprite);
    
    //  Render units
    for(auto &it: friendlyQueue)
        {
            window->draw(it->getSprite());
        }
    for(auto &it: enemyQueue)
        {
            window->draw(it->getSprite());
        }
    gui.draw(GAME_STATE, window);
}

void GameState::resetState()
{
    nextstate = GAME_STATE;
}

int GameState::getNextState()       
{
    return nextstate;
}

void GameState::spawnFriendly()
{
    friendlyQueue.push_back(std::make_shared<Melee> 
        ( melee, true, sf::Vector2f( 40.f, window->getSize().y-200.f ) ) );
    
}

void GameState::spawnEnemy()
{
    enemyQueue.push_back(std::make_shared<Melee> 
        ( melee, false, sf::Vector2f( window->getSize().x - 40.f, window->getSize().y-200.f ) ) );
}

void GameState::updateStage()
{
    stage++;
}