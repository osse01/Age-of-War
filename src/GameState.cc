#include "../include/GameState.h"

#include <iostream>
#include <utility>
#include <cmath>

GameState::GameState(std::shared_ptr<sf::RenderWindow> screen,  std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
:   State(screen, sound, frameDuration), meleeF {}, rangedF {}, meleeE {}, rangedE {}, tankF {}, tankE {}, projectile {}, baseStats {}, friendlyVector {}, enemyVector {}, projectileQueue {},
    backgroundFile { "assets/background.jpeg" }, backgroundTexture {}, backgroundSprite {}, 
    view { sf::FloatRect(0, screen->getSize().y/13, screen->getSize().x/1.5, screen->getSize().y/1.5) },
    zoomFactor { sf::Vector2f( 0.9f, 0.6f ) }, nextState { GAME_STATE }, stage { 1 }, gold{200}, gui { 1, screen }, enemy{frameDuration}
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
    meleeF = reader.returnData("Melee_F", "assets/stage1.txt");
    meleeE = reader.returnData("Melee_E", "assets/stage1.txt");
    rangedF = reader.returnData("Ranged_F", "assets/stage1.txt");
    rangedE = reader.returnData("Ranged_E", "assets/stage1.txt");
    tankF = reader.returnData("Tank_F", "assets/stage1.txt");
    tankE = reader.returnData("Tank_E", "assets/stage1.txt");
    
    projectile = reader.returnData("Projectile", "assets/stage1.txt");
    baseStats = reader.returnData("Base", "assets/stage1.txt");

    friendlyVector.push_back(std::make_shared<Base>(baseStats, true,
    sf::Vector2f(baseStats.spriteDim.x/2, view.getSize().y - baseStats.spriteDim.y/2), frameDuration));

    enemyVector.push_back(std::make_shared<Base>(baseStats, false,
    sf::Vector2f(window->getSize().x - baseStats.spriteDim.x/2, view.getSize().y - baseStats.spriteDim.y/2), frameDuration));

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
                    spawnFriendly(meleeF.type);
                    break;

                case sf::Keyboard::Num2:
                    spawnEnemy(1);
                    break;
                
                case sf::Keyboard::Num3:
                    spawnEnemy(3);
                    break;

                case sf::Keyboard::M:
                    nextState = MENU_STATE;
                    music->stop();
                    break;

                case sf::Keyboard::Escape:
                    nextState = PAUSE_STATE;
                    music->pause();
                    break;
                
                case sf::Keyboard::W:
                    nextState = WIN_STATE;
                    music->stop();
                    break;

                case sf::Keyboard::L:
                    nextState = LOSE_STATE;
                    music->stop();
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
                        spawnFriendly(meleeF.type);
                        break;
                    case 5:
                        spawnFriendly(rangedF.type);
                        break;
                    case 4:
                        spawnFriendly(tankF.type);
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
    if(friendlyVector.back()->isDead())
    {
        nextState = LOSE_STATE;
        return;
    }
    if(enemyVector.back()->isDead())
    {
        nextState = WIN_STATE;
        return;
    }
    {
        sf::Mouse mouse {};
        int margin {static_cast<int>(window->getSize().x/20)};
        int viewLeft {static_cast<int>(view.getCenter().x - view.getSize().x/2)};
        int viewRight {static_cast<int>(view.getCenter().x + view.getSize().x/2)};

        if (mouse.getPosition(*window).x+10 < margin &&  viewLeft > 0)
        {
            view.move(-200*(frameDuration->asSeconds()), 0);
        }
        else if (mouse.getPosition(*window).x > 19*margin && viewRight < static_cast<int>(window->getSize().x-10))
        {
            view.move(200*(frameDuration->asSeconds()), 0);
        }
    }

    //----PROJECTILES----
    int i { 0 };
    for (auto &it: projectileQueue)
    {
        if (it->getSprite().getPosition().y >= window->getSize().y || it->isDead() )
        {
            deleteEntities.push_back(i);
        }
        i++;
        it->updatePos();
    }
    for (int j: deleteEntities)
    {
        projectileQueue.erase( projectileQueue.begin() + j );
    }
    deleteEntities.clear();
    i = 0;

//----FRIENDS----
    for(auto &it: friendlyVector)
        {
            if ( it->isDead() )
            {
                deleteEntities.push_back(i);
            }
            i++;
            it->updatePos();
            if (abs(it->getSprite().getPosition().x - enemyVector.at(0)->getSprite().getPosition().x) 
                <= it->getRange())
            {
                std::shared_ptr<Projectile> tmpProjectile {it->spawnProjectile(projectile, frameDuration, sf::Vector2f(0,0))};
                if ( tmpProjectile != nullptr)
                {
                    projectileQueue.push_back(tmpProjectile);
                }
            }
        }
    for (int j: deleteEntities)
    {
        friendlyVector.erase( friendlyVector.begin() + j );
    }
    deleteEntities.clear();
    i = 0;

//----ENEMIES----   
    for(auto &it: enemyVector)
        {
            if ( it->isDead() )
            {
                deleteEntities.push_back(i);
                gold += it->getDeathValue();
            }
            i++;
            it->updatePos();
        }
    for (int j: deleteEntities)
    {
        enemyVector.erase( enemyVector.begin() + j );
    }
    deleteEntities.clear();

    handleCollisions();
    enemyPlay();

}

void GameState::handleCollisions()
{
    // Handle Collision between Friendly and Enemy
    if ( friendlyVector.size() > 0 && enemyVector.size() > 0 )
    {
        if ( friendlyVector.at(0)->collides(  enemyVector.at(0) ) )
        {
            friendlyVector.at(0) ->handleCollision(1, enemyVector.at(0)->getDamage());
            enemyVector.at(0)    ->handleCollision(1, friendlyVector.at(0)->getDamage());
        }
    }
    
    
    // Handle Collision between Enemies
    int behind{ 1 };
    for(int inFront{ 0 }; inFront < static_cast<int>(enemyVector.size()) - 1; inFront++, behind++)
        { 
            if( enemyVector.at(behind)->collides( enemyVector.at(inFront) ) )
            {
                // Enemy Behind waits for Enemy in Front
                enemyVector.at(behind)->handleCollision();
            }
        }
    
    // Handle Collision between Friends
    behind = 1;
    for( int inFront{ 0 }; inFront < static_cast<int>(friendlyVector.size()) - 1; inFront++, behind++ )
        { 
            if( friendlyVector.at(behind)->collides( friendlyVector.at(inFront) ) )
            {
                // Friend Behind waits for Friend in Front
                friendlyVector.at(behind)->handleCollision();
            }
        }

    // Handle Collision between Projectiles and Entities
    for (auto &itProjectile : projectileQueue)
    {
        if (itProjectile->getIsFriendly())
        {
            for (auto &itEnemy : enemyVector)
            {
                if (itProjectile->collides(itEnemy->getBox()))
                {
                    itEnemy->handleCollision(2, itProjectile->getDamage());
                    itProjectile->handleCollision();
                }
            }
        }
        else
        {
            for (auto &itFriendly : friendlyVector)
            {
                if (itProjectile->collides(itFriendly->getBox()))
                {
                    itFriendly->handleCollision(2, itProjectile->getDamage());
                    itProjectile->handleCollision();
                }
            }
        }
    }
}

void GameState::renderFrame()  
{
    window->setView(view);
    
    //  Fix Background
    window->clear(sf::Color(255, 255, 255));

    //backgroundSprite.setScale(zoomFactor*0.694422f);
    
    window->draw(backgroundSprite);
    
    //  Render units
    for(auto &it: friendlyVector)
    {
        window->draw(it->getSprite());
    }
    for(auto &it: enemyVector)
    {
        window->draw(it->getSprite());
    }
    for(auto &it: projectileQueue)
    {
        window->draw(it->getSprite());
    }
    window->setView(window->getDefaultView());
    gui.draw(GAME_STATE, window, gold);
}

void GameState::resetState()
{
    nextState = GAME_STATE;
}

int GameState::getNextState()       
{
    return nextState;
}

void GameState::spawnFriendly(std::string troop)
{
    auto it = friendlyVector.end()-1;
    if (troop == meleeF.type)
    {
        if (gold >= meleeF.cost)
        {
            gold -= meleeF.cost;
            // Läs på om emplace
            // Lös kollision
            friendlyVector.insert(it, std::make_shared<Melee> 
            ( meleeF, true, sf::Vector2f( 40.f, 8*window->getSize().y/13 ) , frameDuration) );
        }
    }
    else if (troop == rangedF.type)
    {
        if (gold >= rangedF.cost)
        {
            gold -= rangedF.cost;
            friendlyVector.insert(it, std::make_shared<Ranged> 
             ( rangedF, true, sf::Vector2f( 40.f, 8*window->getSize().y/13 ) , frameDuration ) );
        }
    }
    else if (troop == tankF.type)
    {
        if (gold >= tankF.cost)
        {
            gold -= tankF.cost;
            friendlyVector.insert(it, std::make_shared<Tank> 
              ( tankF, true, sf::Vector2f( 40.f, 8*window->getSize().y/13 ) , frameDuration ) );
        }
    }
    else
    {
        throw std::logic_error("\n  >> Error, Unidentified troop type. "
        "Error in GameState::spawnFriendly(std::string). \n");
    }
    
    
}

void GameState::spawnEnemy(int type)
{
    auto it = enemyVector.end()-1;

    switch ( type )
    {
        case 1:
            enemyVector.insert(it, std::make_shared<Melee> 
                ( meleeE, false, sf::Vector2f( window->getSize().x-40.f, 8*window->getSize().y/13 ), frameDuration ) );
            break;
        case 2:
            enemyVector.insert(it, std::make_shared<Ranged> 
                ( rangedE, false, sf::Vector2f( window->getSize().x-40.f, 8*window->getSize().y/13 ), frameDuration ) );
            break;
        case 3:
            enemyVector.insert(it, std::make_shared<Tank> 
                ( tankE, false, sf::Vector2f( window->getSize().x-40.f, 8*window->getSize().y/13 ), frameDuration ) );
            break;
        default:
            break;
    };
}

void GameState::updateStage()
{
    stage++;
}

void GameState::enemyPlay()
{
    std::vector<int> play = enemy.enemyPlay();
    for(int type : play)
    {
        spawnEnemy(type);
    }
}
