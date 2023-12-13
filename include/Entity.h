#ifndef ENTITY_H
#define ENTITY_H

#include "Projectile.h"
#include "FileReader.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <experimental/random>
#include "memory"

class Entity
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    Entity(FileReader::Data&, std::string, bool, sf::Vector2f, std::shared_ptr<sf::Time>);
    virtual ~Entity() = default;
        
    // FUNCTIONS
    virtual std::shared_ptr<Projectile> spawnProjectile( FileReader::Data&,
                                                         std::shared_ptr<sf::Time>, 
                                                         sf::Vector2f );

    virtual bool  buyTurret ( FileReader::Data&, bool, std::shared_ptr<sf::Time>, 
                              std::map<std::string, std::shared_ptr<sf::Sound>> )
                              { return true; };

    virtual sf::Sprite& getSprite           ();
    sf::RectangleShape  getBox              ();
    void                playSound           ( std::map<std::string, std::shared_ptr<sf::Sound>> );
    bool                collides            ( std::shared_ptr<Entity> );

    virtual void        showHP              (std::shared_ptr<sf::RenderWindow>) {};
    virtual bool        inRange             ( std::shared_ptr<Entity> ) = 0;
    virtual void        handleCollision     ( int = 0, int = 0 )        = 0;
    virtual void        updatePos           ()                          = 0;
    virtual int         getDamage           () { return 0;   };
    virtual int         getDeathValue       () { return 0;   };
    virtual float       getCurrentCooldown  () { return 0.f; };
    
    virtual void        specialAttack       () {};
    bool                getIsFriendly       ();
    bool                isDead              ();
    int                 getHP               ();

protected:
    // VARIABLES
    std::shared_ptr<sf::Time>   frameDuration;
    sf::RectangleShape          boundingbox; 
    sf::IntRect                 rectSourceSprite;
    sf::Texture                 texture;
    sf::Sprite                  sprite;
    
    float                       hp;
    float                       xpos;
    float                       ypos;
    bool                        isFriendly;
    bool                        hasCollided;

    int                         actionState;
    int                         spriteCounter;
    int                         audioNumber;
};

#endif