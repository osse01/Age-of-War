#include "Entity.h"

Entity::Entity(bool FRIENDLY, double xpos, double ypos, int hp, sf::Sprite & sprite,
               sf::RectangleShape & boundingbox, std::string & texturePath)
    
    : xpos{ xpos }, ypos{ ypos }, hp{ hp }, IS_FRIENDLY{ FRIENDLY }, 
      TEXTURE{ sf::Texture::loadFromFile( texturePath ) },
      sprite{ sprite }, boundingbox{ boundingbox }
{
    sprite.setTexture(TEXTURE);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));
    boundingbox.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2));

    sprite.setPosition( xpos, ypos );
    boundingbox.setPosition( xpos, ypos );
    sprite.setScale(sf::Vector2f(-0.1f,0.1f)); // scale needs to be fixed somehow
}

sf::Sprite Entity::getSprite() const &
{
    return sprite;
}

bool Entity::collides( Entity* const other ) const
{
    // Check whether this collides with other
    return boundingbox.getGlobalBounds().intersects(
            ( other->boundingbox.getGlobalBounds() ) );
}