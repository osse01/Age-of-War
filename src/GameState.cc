#include "../include/GameState.h"

#include <iostream>
#include <utility>
#include <cmath>

GameState::GameState(std::shared_ptr<sf::RenderWindow> screen, FileReader::Data& dataMap,  std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
:   State(screen, dataMap, sound, frameDuration), friendlyVector {}, enemyVector {}, projectileQueue {},
    backgroundTexture {},  groundTexture{}, woodsTexture{}, backgroundSprite {}, groundSprite{}, woodsSprite {},
    view { sf::FloatRect(0, screen->getSize().y/13, screen->getSize().x/1.5, screen->getSize().y/1.5) },
    zoomFactor { sf::Vector2f( 0.9f, 0.6f ) }, nextState { GAME_STATE }, stage { 1 }, gold{200}, gui { GAME_STATE, screen, dataMap }, enemy{frameDuration}
{
    music->play();      

    //  Load in Background Image
    if(!(backgroundTexture.loadFromFile(dataMap.files["Background"]) && groundTexture.loadFromFile(dataMap.files["Ground"]) && woodsTexture.loadFromFile(dataMap.files["Trees"])))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in GameState::GameState().");
    }
    //  Setup Background Image and ground image
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

    friendlyVector.push_back(std::make_shared<Base>(dataMap, true,
    sf::Vector2f(window->getSize().x/20, 5*view.getSize().y/7+window->getSize().y/13), frameDuration));

    enemyVector.push_back(std::make_shared<Base>(dataMap, false,
    sf::Vector2f(groundSprite.getGlobalBounds().width/2, 5*view.getSize().y/7+window->getSize().y/13), frameDuration));

}

GameState::~GameState()
{music->stop();}

void GameState::handleEvent(sf::Event event)
//  ---------------------------------------------
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Num1:
                    spawnFriendly("Melee");
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
                        spawnFriendly("Melee");
                        break;
                    case 5:
                        spawnFriendly("Ranged");
                        break;
                    case 4:
                        spawnFriendly("Tank");
                        break;
                    case 3:
                        spawnFriendly("Turret");
                        break;
                    case 2:
                        {
                        std::vector<std::shared_ptr<Projectile>> tmpVector {friendlyVector.back()->special(dataMap, frameDuration,
                        friendlyVector.back()->getSprite().getPosition(), (groundSprite.getGlobalBounds().width/2) - 2*friendlyVector.back()->getSprite().getGlobalBounds().width)};
                        if ( !tmpVector.empty())
                        {
                            for ( auto tmpProjectile : tmpVector)
                            {
                                projectileQueue.push_back(tmpProjectile);
                            }
                        }
                        break;
                        }
                    case 1:
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
//  direvtion = false => move right
//  ---------------------------------------------
{
    float   scale       { 100 };
    //float   distance    { groundSprite.getGlobalBounds().width/2 };
    float   bScale      { 0.9 };
    float   tScale      { 0.7 };


    if (direction)
    {
        int viewLeft {static_cast<int>(view.getCenter().x - view.getSize().x/2)};
        if (!(viewLeft - 10 < friendlyVector.back()->getSprite().getPosition().x - friendlyVector.back()->getSprite().getGlobalBounds().width/2))
        {
            view.move(-scale*(frameDuration->asSeconds()), 0);
            backgroundSprite.move(-bScale*scale*(frameDuration->asSeconds()), 0);
            woodsSprite.move(-tScale*scale*(frameDuration->asSeconds()), 0);
        }
    }
    else
    {
        int viewRight {static_cast<int>(view.getCenter().x + view.getSize().x/2)};
        if (!(viewRight + 10 > enemyVector.back()->getSprite().getPosition().x + enemyVector.back()->getSprite().getGlobalBounds().width/2))
        {
            view.move(scale*(frameDuration->asSeconds()), 0);
            backgroundSprite.move(bScale*scale*(frameDuration->asSeconds()), 0);
            woodsSprite.move(tScale*scale*(frameDuration->asSeconds()), 0);
        }
    }
}

void GameState::updateLogic()        
//  ---------------------------------------------
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
        
        
            if (mouse.getPosition(*window).x < margin)
            {
                windowPanning(true);
            }
            else if (mouse.getPosition(*window).x > 19*margin)
            {
                windowPanning(false);
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
    sf::Vector2f enemyPos {};
    for(auto &it: friendlyVector)
        {
            if ( it->isDead() )
            {
                deleteEntities.push_back(i);
            }
            i++;
            it->updatePos();
            enemyPos = enemyVector.at(0)->getSprite().getPosition();
            if (abs(it->getSprite().getPosition().x - enemyPos.x) 
                <= it->getRange())
            {
                std::shared_ptr<Projectile> tmpProjectile {it->spawnProjectile(dataMap, frameDuration, enemyPos)};
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
    sf::Vector2f friendlyPos {};
    for(auto &it: enemyVector)
        {
            if ( it->isDead() )
            {
                deleteEntities.push_back(i);
                gold += it->getDeathValue();
            }
            i++;
            it->updatePos();
            friendlyPos = friendlyVector.at(0)->getSprite().getPosition();
            if (abs(it->getSprite().getPosition().x - friendlyPos.x) 
                <= it->getRange())
            {
                std::shared_ptr<Projectile> tmpProjectile {it->spawnProjectile(dataMap, frameDuration, friendlyPos)};
                if ( tmpProjectile != nullptr)
                {
                    projectileQueue.push_back(tmpProjectile);
                }
            }
        }
    for (int j: deleteEntities)
    {
        enemyVector.erase( enemyVector.begin() + j );
    }
    deleteEntities.clear();

    handleCollisions();
    enemyPlay();
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
    
    //  Fix Background
    window->clear(sf::Color(255, 255, 255));

    window->draw(backgroundSprite);
    window->draw(woodsSprite);
    window->draw(groundSprite);    
    
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
    gui.drawHPBar(window, groundSprite, friendlyVector.back()->getHP(), enemyVector.back()->getHP());
    window->setView(window->getDefaultView());
    gui.draw(GAME_STATE, window, gold);
}

void GameState::resetState()
//  ---------------------------------------------
{
    nextState = GAME_STATE;
}

int GameState::getNextState()       
//  ---------------------------------------------
{
    return nextState;
}

void GameState::spawnFriendly(std::string troop)
//  ---------------------------------------------
{
    sf::RectangleShape baseBounds {friendlyVector.back()->getBox()};
    sf::Vector2f spawnPoint { baseBounds.getPosition().x + baseBounds.getGlobalBounds().width/2,
                              baseBounds.getPosition().y + baseBounds.getGlobalBounds().height/2.5};

    auto it = friendlyVector.end()-1;
    if (gold >= dataMap.stats[troop]["cost"])
    {
        gold -= dataMap.stats[troop]["cost"];
        // Läs på om emplace
        // Lös kollision
        if (troop == "Melee")
        {
            friendlyVector.insert(it, std::make_shared<Melee> 
            ( dataMap, true, spawnPoint, frameDuration) );
        }
        else if(troop == "Ranged")
        {
            friendlyVector.insert(it, std::make_shared<Ranged> 
             ( dataMap, true, spawnPoint, frameDuration ) );
        }
        else if(troop == "Tank")
        {
            friendlyVector.insert(it, std::make_shared<Tank> 
             ( dataMap, true, spawnPoint, frameDuration ) );
        }
        else if(troop == "Turret" && friendlyVector.back()->buyTurret(dataMap, true, spawnPoint, frameDuration))
        {}
    }    
}

void GameState::spawnEnemy(int type)
//  ---------------------------------------------
{
    sf::Sprite baseBounds {enemyVector.back()->getSprite()};
    sf::Vector2f spawnPoint { baseBounds.getPosition().x - baseBounds.getGlobalBounds().width/2,
                              baseBounds.getPosition().y + baseBounds.getGlobalBounds().width/2 };

    auto it = enemyVector.end()-1;

    switch ( type )
    {
        case 1:
            enemyVector.insert(it, std::make_shared<Melee> 
                ( dataMap, false, spawnPoint, frameDuration) );
            break;
        case 2:
            enemyVector.insert(it, std::make_shared<Ranged> 
                ( dataMap, false, spawnPoint, frameDuration ) );
            break;
        case 3:
            enemyVector.insert(it, std::make_shared<Tank> 
                ( dataMap, false, spawnPoint, frameDuration ) );
            break;
        default:
            break;
    };
}

void GameState::updateStage()
//  ---------------------------------------------
{
    stage++;
}

void GameState::enemyPlay()
//  ---------------------------------------------
{
    std::vector<int> play = enemy.enemyPlay();
    for(int type : play)
    {
        spawnEnemy(type);
    }
}