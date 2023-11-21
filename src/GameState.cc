#include "../include/GameState.h"

#include <iostream>
#include "utility"
#include <cmath>

GameState::GameState(std::shared_ptr<sf::RenderWindow> screen,  std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
:   State(screen, sound, frameDuration), melee {}, ranged {}, tank {}, projectile {}, friendlyQueue {}, enemyQueue {}, projectileQueue {},
    backgroundFile { "assets/background.jpeg" }, backgroundTexture {},
    backgroundSprite {}, zoomFactor { sf::Vector2f( 0.9f, 0.6f ) }, nextstate { GAME_STATE }, stage { 1 }, gui { 1, screen }
{

    //  Load in Background Image
    if(!backgroundTexture.loadFromFile(backgroundFile))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in GameState::GameState().");
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window->getSize().x / backgroundSprite.getGlobalBounds().width, 
        window->getSize().y / backgroundSprite.getGlobalBounds().height);

    FileReader reader {};
    melee = reader.returnData("Melee", "assets/stage1.txt");
    ranged = reader.returnData("Range", "assets/stage1.txt");
    
    projectile = reader.returnData("Projectile", "assets/stage1.txt");


}

GameState::~GameState()
{}

void GameState::handleEvent(sf::Event event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Num1:
                    spawnFriendly(0);
                    break;

                case sf::Keyboard::Num2:
                    spawnEnemy();
                    break;

                case sf::Keyboard::M:
                    nextstate = MENU_STATE;
                    music->stop();
                    break;

                case sf::Keyboard::Escape:
                    nextstate = PAUSE_STATE;
                    music->pause();
                    break;

                default:
                    break;
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
                        spawnFriendly(0);
                        break;
                    case 5:
                        spawnEnemy();
                        break;
                    case 4:
                        spawnFriendly(1);
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
//----PROJECTILES----
    std::vector<int> deleteEntities{};
    int i {};
    for (auto &it: projectileQueue)
    {
        if (it->getPos().y >= window->getSize().y || it->isDead())
        {
            deleteEntities.push_back(i);
            i++;
            continue;
        }
        it->updatePos();
    }
    for (int j: deleteEntities)
    {
        projectileQueue.erase( projectileQueue.begin() + j );
    }
    deleteEntities.clear();
    i = 0;

//----FRIENDS----
    for(auto &it: friendlyQueue)
        {
            if ( it->isDead() )
            {
                deleteEntities.push_back(i);
            }
            i++;
            std::cout << frameDuration->asSeconds() << std::endl;
            it->updatePos();
            if (enemyQueue.size() > 0 && it->getType() == 2 && 
               ( it->incrAtkCounter() ) >= ranged.attackSpeed &&
               (abs(it->getPos().x - enemyQueue.at(0)->getPos().x) <= ranged.range * it->getSprite().getGlobalBounds().width))
            {
                projectileQueue.push_back(std::make_shared<Projectile>
                    (projectile, true, it->getPos(), frameDuration));
                    it->resetAtkCounter();
            }
        }
    for (int j: deleteEntities)
    {
        friendlyQueue.erase( friendlyQueue.begin() + j );
    }

//----ENEMIES----
    deleteEntities.clear();
    i = 0;
    for(auto &it: enemyQueue)
        {
            if ( it->isDead() )
            {
                deleteEntities.push_back(i);
            }
            it->updatePos();
            i++;
        }
    for (int j: deleteEntities)
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
    // Collision between projectile and Enemies
    for ( auto &itProjectile: projectileQueue )
    {
        for ( auto &itEnemy: enemyQueue)
        {
            if ( itProjectile->collides(itEnemy) )
            {
                itEnemy->handleCollision( 1, itProjectile->getDamage());
                itProjectile->changeHp(0);
            }
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
    for(auto &it: projectileQueue)
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

void GameState::spawnFriendly(int type)
{
    switch ( type )
    {
    case 0:
        friendlyQueue.push_back(std::make_shared<Melee> 
            ( melee, true, sf::Vector2f( 40.f, window->getSize().y-200.f ), frameDuration ) );
        break;
    case 1:
        friendlyQueue.push_back(std::make_shared<Range> 
            ( ranged, true, sf::Vector2f( 40.f, window->getSize().y-200.f ), frameDuration ) );
        break;
    default:
        break;
    };
}

void GameState::spawnEnemy()
{
    enemyQueue.push_back(std::make_shared<Melee> 
        ( melee, false, sf::Vector2f( window->getSize().x - 40.f, window->getSize().y-200.f ), frameDuration ) );
}

void GameState::updateStage()
{
    stage++;
}
