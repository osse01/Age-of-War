#include "../include/GameState.h"

#include <iostream>
#include <utility>

GameState::GameState(std::shared_ptr<sf::RenderWindow> screen,  std::shared_ptr<sf::Music> sound, std::shared_ptr<sf::Time> frameDuration)
:   State(screen, sound, frameDuration), melee {}, ranged {}, tank {}, friendlyQueue {}, enemyQueue {},
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
    backgroundSprite.setScale(window->getSize().x / backgroundSprite.getGlobalBounds().width, window->getSize().y / backgroundSprite.getGlobalBounds().height);

    FileReader reader {};
    melee = reader.returnData("Melee", "assets/stage1.txt");
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
    for(auto &it: friendlyQueue)
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
    for(auto &it: enemyQueue)
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
            friendlyQueue.at(0) ->handleCollision(1, enemyQueue.at(0)->getDamage(), frameDuration);
            enemyQueue.at(0)    ->handleCollision(1, friendlyQueue.at(0)->getDamage(), frameDuration);
        }
    }
    
    // Handle Collision between Enemies
    int behind{ 1 };
    for(int inFront{ 0 }; inFront < static_cast<int>(enemyQueue.size()) - 1; inFront++, behind++)
        { 
            if( enemyQueue.at(behind)->collides( enemyQueue.at(inFront) ) )
            {
                // Enemy Behind waits for Enemy in Front
                enemyQueue.at(behind)->handleCollision(0, 0, frameDuration);
            }
        }
    
    // Handle Collision between Friends
    behind = 1;
    for( int inFront{ 0 }; inFront < static_cast<int>(friendlyQueue.size()) - 1; inFront++, behind++ )
        { 
            if( friendlyQueue.at(behind)->collides( friendlyQueue.at(inFront) ) )
            {
                // Friend Behind waits for Friend in Front
                friendlyQueue.at(behind)->handleCollision(0, 0, frameDuration);
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
    for(auto &it: friendlyQueue)
        {
            window->draw(it->getSprite());
        }
    for(auto &it: enemyQueue)
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
        std::cout << gold << std::endl;
        if (gold >= melee.cost)
        {
            gold -= melee.cost;
            friendlyQueue.push_back(std::make_shared<Melee> 
            ( melee, true, sf::Vector2f( 40.f, 8*window->getSize().y/13 ) ) );
        }
    }
}

void GameState::spawnEnemy()
{
    enemyQueue.push_back(std::make_shared<Melee> 
        ( melee, false, sf::Vector2f( window->getSize().x - 40.f, 8*window->getSize().y/13 ) ) );
}

void GameState::updateStage()
{
    stage++;
}