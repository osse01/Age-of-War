#include "catch.hpp"
#include "memory"
#include "../include/GameState.h"

// All the tests for the melee Class.
// 

TEST_CASE ("CONSTRUCTORS AND GETTERS")

{
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>();
    sf::Clock clock {};
    FileReader filereader {window};
    std::shared_ptr<sf::Time> frameDuration = std::make_shared<sf::Time>( clock.getElapsedTime() );
    
    SECTION ("THROWS")
    {
        CHECK_THROWS ( filereader.returnData("Something wrong") );
    }
    
    FileReader::Data data = filereader.returnData("test/test_data.txt"); 
    data.windowScale = 1;
    
    
    SECTION ("GETTERS")
    {
        Melee meleeTroop {data, true, sf::Vector2f(0,0), frameDuration};
        Melee enemy {data, false, sf::Vector2f(0,0), frameDuration};
        std::shared_ptr<Entity> ptr = std::make_shared<Melee> ( data, false, sf::Vector2f(0,0), frameDuration );

        //TROOP
        CHECK ( meleeTroop.spawnProjectile(data, frameDuration, sf::Vector2f(0,0)) == nullptr );

        //Should return damage every 4th time we change Sprite
        CHECK ( meleeTroop.getDamage() == 0 );
        meleeTroop.handleCollision(1,0);          // calls takeDamage() and changeSprite()
        
        // getDamage return 0 most of the time.
        while ( meleeTroop.getDamage() == 0)
        {
            meleeTroop.handleCollision(1,0);
        }
        CHECK ( meleeTroop.getDamage() == data.stats["Melee"]["damage"] );
        
        CHECK ( meleeTroop.getDeathValue() == data.stats["Melee"]["deathValue"] );
        
        CHECK ( meleeTroop.inRange(ptr) == false );
        
        CHECK ( meleeTroop.getHP() == data.stats["Melee"]["hp"] );
        
        CHECK ( meleeTroop.getBox().getGlobalBounds().width == 
                                data.boxSize["Melee"].x );
        CHECK ( meleeTroop.getBox().getGlobalBounds().height == 
                                data.boxSize["Melee"].y );

        // Rest of the tests are only visuals.
        
        CHECK (  meleeTroop.getIsFriendly() );
        CHECK_FALSE ( enemy.getIsFriendly() );


        sf::Vector2f pos = sf::Vector2f(0,0);
        Melee meleeTroop1 {data, true, pos, frameDuration};


        CHECK ( meleeTroop1.getSprite().getPosition().x ==  pos.x);
        meleeTroop1.updatePos();          // Move forward
        CHECK ( meleeTroop1.getSprite().getPosition().x ==
                pos.x + data.stats["Melee"]["movementSpeed"]  * abs(meleeTroop1.getSprite().getScale().x) * frameDuration->asSeconds()); //scale is negative for friendlies
        meleeTroop1.handleCollision(1,0); // Reset movement
        CHECK ( meleeTroop1.getSprite().getPosition().x == pos.x);
    }

    SECTION ("COLLISION")
    {
        Melee meleeTroop {data, true, sf::Vector2f(0,0), frameDuration};
        Melee enemy {data, false, sf::Vector2f(0,0), frameDuration};
        Melee notCollideTroop {data, false, sf::Vector2f(250,250), frameDuration};

        CHECK_FALSE ( meleeTroop.isDead() );
        meleeTroop.handleCollision(2, 1000); // 2nd arg is damage
        // takeDamage() runs through handleCollision()
        CHECK ( meleeTroop.isDead() );
        
        CHECK ( meleeTroop.collides( std::make_shared<Melee>(enemy) ) );
        CHECK_FALSE ( meleeTroop.collides( std::make_shared<Melee>(notCollideTroop) ) );
    }
}
