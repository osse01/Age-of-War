#include "../include/GameState.h"

#include <iostream>
#include <utility>

GameState::GameState(std::shared_ptr<sf::RenderWindow> screen,  std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
:   State(screen, sound, frameDuration), melee {}, ranged {}, tank {}, baseStats {}, friendlyVector {}, enemyVector {},
    backgroundFile { "assets/background.jpeg" }, backgroundTexture {}, backgroundSprite {}, 
    view { sf::FloatRect(0, screen->getSize().y/13, screen->getSize().x/1.5, screen->getSize().y/1.5) },
    zoomFactor { sf::Vector2f( 0.9f, 0.6f ) }, nextstate { GAME_STATE }, stage { 1 }, gold{200}, gui { 1, screen }
{
    //window->setFramerateLimit(18);

    //  Load in Background Image
    if(!backgroundTexture.loadFromFile(backgroundFile))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in GameState::GameState().");
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(window->getSize().x / backgroundSprite.getGlobalBounds().width,
    window->getSize().y / backgroundSprite.getGlobalBounds().height);

    FileReader reader {};
    melee = reader.returnData("Melee", "assets/stage1.txt");
    baseStats = reader.returnData("Base", "assets/stage1.txt");

    friendlyVector.push_back(std::make_shared<Base>(baseStats, true,
    sf::Vector2f(baseStats.spriteDim.x/2, window->getSize().y-baseStats.spriteDim.y/2)));
    window->setView(view);
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
                    spawnFriendly(melee.type);
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
                        spawnFriendly(melee.type);
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
    {
        sf::Mouse mouse {};
        int margin {static_cast<int>(window->getSize().x/20)};
        if (mouse.getPosition(*window).x < margin)
        {
            view.move(-200*(frameDuration->asSeconds()), 0);
            window->setView(view);
        }
        else if (mouse.getPosition(*window).x > 19*margin)
        {
            view.move(200*(frameDuration->asSeconds()), 0);
            window->setView(view);
        }
    }

    std::vector<int> deadEntitiesFriendly{};
    std::vector<int> deadEntitiesEnemy{};
    int i {};
    for(auto &it: friendlyVector)
        {
            if ( it->isDead() )
            {
                deadEntitiesFriendly.push_back(i);
                gold += it->getDeathValue();
            }
            it->updatePos(frameDuration);
            i++;
        }
    i = 0;
    for(auto &it: enemyVector)
        {
            if ( it->isDead() )
            {
                deadEntitiesEnemy.push_back(i);
            }
            it->updatePos(frameDuration);
            i++;
        }
    for (int j: deadEntitiesFriendly)
    {
        friendlyVector.erase( friendlyVector.begin() + j );
    }
    for (int j: deadEntitiesEnemy)
    {
        enemyVector.erase( enemyVector.begin() + j );
    }
    handleCollisions();
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
                enemyVector.at(behind)->handleCollision(0, 0);
            }
        }
    
    // Handle Collision between Friends
    behind = 1;
    for( int inFront{ 0 }; inFront < static_cast<int>(friendlyVector.size()) - 1; inFront++, behind++ )
        { 
            if( friendlyVector.at(behind)->collides( friendlyVector.at(inFront) ) )
            {
                // Friend Behind waits for Friend in Front
                friendlyVector.at(behind)->handleCollision(0, 0);
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
    window->setView(window->getDefaultView());
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

void GameState::spawnFriendly(std::string troop)
{
    if (troop == melee.type)
    {
        if (gold >= melee.cost)
        {
            gold -= melee.cost;
            friendlyVector.push_back(std::make_shared<Melee> 
            ( melee, true, sf::Vector2f( 40.f, 8*window->getSize().y/13 ) ) );
        }
    }
    else if (troop == ranged.type)
    {
        if (gold >= ranged.cost)
        {
            gold -= ranged.cost;
            // friendlyQueue.push_back(std::make_shared<Ranged> 
            //  ( ranged, true, sf::Vector2f( 40.f, 8*window->getSize().y/13 ) ) );
        }
    }
    else if (troop == tank.type)
    {
        if (gold >= tank.cost)
        {
            gold -= tank.cost;
            //friendlyQueue.push_back(std::make_shared<Tank> 
            //  ( tank, true, sf::Vector2f( 40.f, 8*window->getSize().y/13 ) ) );
        }
    }
    else
    {
        throw std::logic_error("\n  >> Error, Unidentified troop type. "
        "Error in GameState::spawnFriendly(std::string). \n");
    }
}

void GameState::spawnEnemy()
{
    enemyVector.push_back(std::make_shared<Melee> 
        ( melee, false, sf::Vector2f( window->getSize().x - 40.f, window->getSize().y-200.f ) ) );
}

void GameState::updateStage()
{
    stage++;
}