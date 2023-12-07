#include "../include/GameState.h"

#include <iostream>
#include <utility>
#include <cmath>


GameState::GameState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap,  std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
:   State(screen, dataMap, sound, frameDuration), friendlyVector {}, enemyVector {}, projectileQueue {},
    backgroundTexture {},  groundTexture{}, woodsTexture{}, backgroundSprite {}, groundSprite{}, woodsSprite {},
    view { sf::FloatRect(0, screen->getSize().y/13, screen->getSize().x/1.5, screen->getSize().y/1.5) },
    zoomFactor { sf::Vector2f( 0.9f, 0.6f ) }, nextState { GAME_STATE }, gold{200}, gui { GAME_STATE, screen, dataMap }, enemyStats{dataMap}, enemy{enemyStats, frameDuration}
{
    music->play();      

    //  Load in Background Image
    if(!(backgroundTexture.loadFromFile(dataMap.files["Background"]) && groundTexture.loadFromFile(dataMap.files["Ground"]) && woodsTexture.loadFromFile(dataMap.files["Trees"])))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in GameState::GameState().");
    }
    //  Setup Ground Image and Background Image
    groundSprite.setTexture(groundTexture);
    groundSprite.setOrigin(groundSprite.getGlobalBounds().width/2, groundSprite.getGlobalBounds().height); 
    groundSprite.setPosition(window->getSize().x/2, view.getSize().y + screen->getSize().y/13);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setOrigin(backgroundSprite.getGlobalBounds().width/2, backgroundSprite.getGlobalBounds().height/2);
    backgroundSprite.setPosition(backgroundSprite.getGlobalBounds().width/2, backgroundSprite.getGlobalBounds().height/2);
    backgroundSprite.scale(1.75, 1);

    woodsSprite.setScale(1, 1);
    woodsTexture.setRepeated(true);
    woodsSprite.setTexture(woodsTexture);
    woodsSprite.setTextureRect(sf::Rect(0,0,
     static_cast<int>(8*woodsSprite.getGlobalBounds().width),static_cast<int>(woodsSprite.getGlobalBounds().height)));
    woodsSprite.setOrigin(woodsSprite.getGlobalBounds().width/2, woodsSprite.getGlobalBounds().height);
    woodsSprite.setPosition(groundSprite.getPosition().x, groundSprite.getPosition().y  ); 
    woodsSprite.setScale(0.5, 0.5);

    // Create Friendly Base
    friendlyVector.push_back(std::make_shared<Base>(dataMap, true,
    sf::Vector2f(window->getSize().x/20, 5*view.getSize().y/7+window->getSize().y/13), frameDuration));

    // Create Enemy Base
    enemyVector.push_back(std::make_shared<Base>(dataMap, false,
    sf::Vector2f(window->getSize().x - window->getSize().x/20, 5*view.getSize().y/7+window->getSize().y/13), frameDuration));

}

GameState::~GameState()
{music->stop();}

void GameState::handleEvent(sf::Event event)
//  ---------------------------------------------
{
    switch (event.type)
    {
        // Handle Keyboard Input
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Num1:
                    spawnFriendly("Melee");
                    break;

                case sf::Keyboard::Num2:
                    spawnFriendly("Ranged");
                    break;
                
                case sf::Keyboard::Num3:
                    spawnFriendly("Tank");
                    break;

                case sf::Keyboard::Escape:
                    nextState = PAUSE_STATE;
                    break;

                default:
                    break;
            }
            break;

        // Hanndle Mouse Clicks
        case sf::Event::MouseButtonPressed:
        {
            sf::Event::MouseButtonEvent mouse { event.mouseButton };
            if (mouse.button == sf::Mouse::Button::Left)
            {
                switch (gui.buttonClicked(GAME_STATE, mouse.x, mouse.y))
                {
                    case SPAWN_MELEE:
                        spawnFriendly("Melee");
                        break;
                    case SPAWN_RANGED:
                        spawnFriendly("Ranged");
                        break;
                    case SPAWN_TANK:
                        spawnFriendly("Tank");
                        break;
                    case BUY_TURRET:
                        spawnFriendly("Turret");
                        break;
                    case PAUSE:
                        nextState = PAUSE_STATE;
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

void GameState::windowPanning(bool direction)
//  ---------------------------------------------
//  direction = true  => move left
//  direction = false => move right
//  ---------------------------------------------
{
    float   scale       { 100 };
    //float   distance    { groundSprite.getGlobalBounds().width/2 };
    float   backgroundScale      { 0.9 };
    float   woodsScale      { 0.7 };

    // Pan Left
    if (direction)
    {
        int viewLeft {static_cast<int>(view.getCenter().x - view.getSize().x/2)};
        if (!(viewLeft - 10 < friendlyVector.back()->getSprite().getPosition().x - friendlyVector.back()->getSprite().getGlobalBounds().width/2))
        {
            view.move(-scale*(frameDuration->asSeconds()), 0);
            backgroundSprite.move(-backgroundScale*scale*(frameDuration->asSeconds()), 0);
            woodsSprite.move(-woodsScale*scale*(frameDuration->asSeconds()), 0);
        }
    }

    // Pan Right
    else
    {
        int viewRight {static_cast<int>(view.getCenter().x + view.getSize().x/2)};
        if (!(viewRight + 10 > enemyVector.back()->getSprite().getPosition().x + enemyVector.back()->getSprite().getGlobalBounds().width/2))
        {
            view.move(scale*(frameDuration->asSeconds()), 0);
            backgroundSprite.move(backgroundScale*scale*(frameDuration->asSeconds()), 0);
            woodsSprite.move(woodsScale*scale*(frameDuration->asSeconds()), 0);
        }
    }
}

void GameState::updateLogic()        
//  ---------------------------------------------
{
    // Lose the Game if Player Base is Destroyed
    if(friendlyVector.back()->isDead())
    {
        nextState = LOSE_STATE;
        return;
    }

    // Win the Game if Enemy Base is Destroyed
    if(enemyVector.back()->isDead())
    {
        nextState = WIN_STATE;
        return;
    }

    // View Panning
    {
        sf::Mouse mouse {};
        int margin {static_cast<int>(window->getSize().x/20)};
        
            // Pan Left
            if (mouse.getPosition(*window).x < margin)
            {
                windowPanning(true);
            }

            // Pan Right
            else if (mouse.getPosition(*window).x > 19*margin)
            {
                windowPanning(false);
            }
    }
    
    int i { 0 };
    //----PROJECTILES---
    for (auto &it: projectileQueue)
    {
        // Remove Projectile after Collision with Entity or Ground
        if (it->getSprite().getPosition().y >= window->getSize().y || it->isDead() )
        {
            deleteEntities.push_back(i);
        }
        i++;

        // Update Projectile Position
        it->updatePos();
    }
    // Delete Removed Projectiles
    for (int j: deleteEntities)
    {
        projectileQueue.erase( projectileQueue.begin() + j );
    }
    deleteEntities.clear();
    i = 0;

    //----FRIENDS----
    sf::Vector2f enemyPos {};
    for(auto &it: friendlyVector)
        {
             // Remove Troop if It Has Been Killed
            if ( it->isDead() )
            {
                deleteEntities.push_back(i);
            }
            i++;

            // Update Troop Position
            it->updatePos();

            // Shoot Projectile if Enemy is In Range
            enemyPos = enemyVector.at(0)->getSprite().getPosition();
            if (abs(it->getSprite().getPosition().x - enemyPos.x) 
                <= it->getRange())
            {
                std::shared_ptr<Projectile> tmpProjectile {it->spawnProjectile(dataMap, frameDuration, enemyPos)};
                // Add Projectile to Projectile Queue
                if ( tmpProjectile != nullptr)
                {
                    projectileQueue.push_back(tmpProjectile);
                }
            }
        }
    // Delete Removed Troops
    for (int j: deleteEntities)
    {
        friendlyVector.erase( friendlyVector.begin() + j );
    }
    deleteEntities.clear();
    i = 0;

    //----ENEMIES----   
    sf::Vector2f friendlyPos {};
    for(auto &it: enemyVector)
        {
            // Remove Troop if It Has Been Killed
            if ( it->isDead() )
            {
                deleteEntities.push_back(i);
                gold += it->getDeathValue();
            }
            i++;

            // Update Troop Position
            it->updatePos();

            // Shoot Projectile if Enemy is In Range
            friendlyPos = friendlyVector.at(0)->getSprite().getPosition();
            if (abs(it->getSprite().getPosition().x - friendlyPos.x) 
                <= it->getRange())
            {
                std::shared_ptr<Projectile> tmpProjectile {it->spawnProjectile(dataMap, frameDuration, friendlyPos)};
                // Add Projectile to Projectile Queue
                if ( tmpProjectile != nullptr)
                {
                    projectileQueue.push_back(tmpProjectile);
                }
            }
        }
    // Delete Removed Troops
    for (int j: deleteEntities)
    {
        enemyVector.erase( enemyVector.begin() + j );
    }
    deleteEntities.clear();

    // Handle Collisions
    handleCollisions();

    // Play the Enemy Algorithm
    enemyPlay();
    
    // Update Logic for Graphics
    gui.updateLogic(window, GAME_STATE);
        
}

void GameState::handleCollisions()
//  ---------------------------------------------
{
    // Handle Collision between Friendly and Enemy
    if ( friendlyVector.size() > 0 && enemyVector.size() > 0 )
    {
        if ( friendlyVector.at(0)->collides(  enemyVector.at(0) ) )
        {
            friendlyVector.at(0) ->handleCollision(2, enemyVector.at(0)->getDamage());
            enemyVector.at(0)    ->handleCollision(2, friendlyVector.at(0)->getDamage());
        }
    }
    
    
    // Handle Collision between Enemies
    int behind{ 1 };
    for(int inFront{ 0 }; inFront < static_cast<int>(enemyVector.size()) - 1; inFront++, behind++)
        { 
            if( enemyVector.at(behind)->collides( enemyVector.at(inFront) ) )
            {
                // Enemy Behind waits for Enemy in Front
                enemyVector.at(behind)->handleCollision(1);
            }
        }
    
    // Handle Collision between Friends
    behind = 1;
    for( int inFront{ 0 }; inFront < static_cast<int>(friendlyVector.size()) - 1; inFront++, behind++ )
        { 
            if( friendlyVector.at(behind)->collides( friendlyVector.at(inFront) ) )
            {
                // Friend Behind waits for Friend in Front
                friendlyVector.at(behind)->handleCollision(1);
            }
        }

    // Handle Collision between Projectiles and Entities
    for (auto &itProjectile : projectileQueue)
    {
        // Collision between Friendly Projectiles and Enemy Entities
        if (itProjectile->getIsFriendly())
        {
            for (auto &itEnemy : enemyVector)
            {
                if (itProjectile->collides(itEnemy->getBox()))
                {
                    itEnemy->handleCollision(3, itProjectile->getDamage());
                    itProjectile->handleCollision();
                }
            }
        }

        // Collision between Enemy Projectiles and Friendly Entities
        else
        {
            for (auto &itFriendly : friendlyVector)
            {
                if (itProjectile->collides(itFriendly->getBox()))
                {
                    itFriendly->handleCollision(3, itProjectile->getDamage());
                    itProjectile->handleCollision();
                }
            }
        }
    }
}

void GameState::renderFrame()  
//  ---------------------------------------------
{
    window->setView(view);
    
    // Render Background
    window->clear(sf::Color(255, 255, 255));
    window->draw(backgroundSprite);
    window->draw(woodsSprite);
    window->draw(groundSprite);    
    
    // Render units
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

    // Render Stationary Graphics
    gui.drawHPBar(window, groundSprite, friendlyVector.back()->getHP(), enemyVector.back()->getHP());
    window->setView(window->getDefaultView());
    gui.draw(GAME_STATE, window, gold);
}

void GameState::resetState()
//  ---------------------------------------------
// Reset nextState variable to Game State
{
    nextState = GAME_STATE;
}

int GameState::getNextState()       
//  ---------------------------------------------
// Return Next State
{
    return nextState;
}

void GameState::spawnFriendly(std::string troopType)
//  ---------------------------------------------
{
    // Set Spawn Point for Troops
    sf::RectangleShape baseBounds {friendlyVector.back()->getBox()};
    sf::Vector2f spawnPoint { baseBounds.getPosition().x + baseBounds.getGlobalBounds().width/2,
                              baseBounds.getPosition().y + baseBounds.getGlobalBounds().height/2.5f};

    // Place in Front of Base in friendlyVector (Base is at end())
    auto it = friendlyVector.end()-1;
    // Check if Player Gold is Greater Than Troop Cost
    if (gold >= dataMap.stats[troopType]["cost"])
    {
        // Remove Troop Cost from Player Gold
        gold -= dataMap.stats[troopType]["cost"];

        // Spawn Correct Troop Type
        if (troopType == "Melee")
        {
            friendlyVector.insert(it, std::make_shared<Melee> 
            ( dataMap, true, spawnPoint, frameDuration) );
        }
        else if(troopType == "Ranged")
        {
            friendlyVector.insert(it, std::make_shared<Ranged> 
             ( dataMap, true, spawnPoint, frameDuration ) );
        }
        else if(troopType == "Tank")
        {
            friendlyVector.insert(it, std::make_shared<Tank> 
             ( dataMap, true, spawnPoint, frameDuration ) );
        }

        // Spawn Turret if None Exist
        // buyTurret Returns False if There Already Exists a Turret
        else if(troopType == "Turret" && friendlyVector.back()->buyTurret(dataMap, true, spawnPoint, frameDuration))
        {}
    }    
}

void GameState::spawnEnemy(int type)
//  ---------------------------------------------
{
    // Set Spawn Point for Troops
    sf::RectangleShape baseBounds {enemyVector.back()->getBox()};
    sf::Vector2f spawnPoint { baseBounds.getPosition().x - baseBounds.getGlobalBounds().width/2,
                              baseBounds.getPosition().y + baseBounds.getGlobalBounds().height/2.5f };
    // Place in Front of Base in friendlyVector (Base is at end())
    auto it = enemyVector.end()-1;

    switch ( type )
    {
        // Spawn Correct Troop Type
        case SPAWN_MELEE:
            enemyVector.insert(it, std::make_shared<Melee> 
                ( enemyStats, false, spawnPoint, frameDuration) );
            break;
        case SPAWN_RANGED:
            enemyVector.insert(it, std::make_shared<Ranged> 
                ( enemyStats, false, spawnPoint, frameDuration ) );
            break;
        case SPAWN_TANK:
            enemyVector.insert(it, std::make_shared<Tank> 
                ( enemyStats, false, spawnPoint, frameDuration ) );
            break;

        // Spawn Turret if None Exist
        // buyTurret Returns False if There Already Exists a Turret
        case BUY_TURRET:
            if(enemyVector.back()->buyTurret(dataMap, false, spawnPoint, frameDuration))
            {}
            break;
        default:
            break;
    };
}


void GameState::enemyPlay()
//  ---------------------------------------------
// Update Enemy Spawn Vector
{
    
    std::vector<int> play = enemy.enemyPlay();
    for(int type : play)
    {
        spawnEnemy(type);
    }
    
}
