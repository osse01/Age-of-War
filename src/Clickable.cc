#include "../include/Clickable.h"

Clickable::Clickable(sf::Vector2f initSize, sf::Vector2f initPosition, Type type)
: size {initSize}, 
  pos {initPosition}, 
  renderTexture{},
  renderSprite{},
  status{Idle},
  type {type}
{
    renderTexture.create(size.x, size.y);
    setPosition(pos);
    setSize(size);
}

Clickable::Clickable(Type type)
: size{sf::Vector2f(0,0)},
  pos{sf::Vector2f(0,0)},
  renderTexture{},
  renderSprite{},
  status{Idle},
  type {type}
{
    status = Idle;
}

bool Clickable::create(unsigned int width, unsigned int height)
{
    return renderTexture.create(width, height);
}

Clickable::Status Clickable::getStatus() const
{
    return status;
}

const sf::Vector2f& Clickable::getPosition() const
{
    return pos;
}

float Clickable::getRotation() const
{
    return renderSprite.getRotation();
}

const sf::Color& Clickable::getColor() const
{
    return renderSprite.getColor();
}

const sf::Vector2f& Clickable::getSize() const
{
    return size;
}
const sf::Vector2f& Clickable::getOrigin() const
{
    return renderSprite.getOrigin();
}

const sf::Vector2f& Clickable::getScale() const
{
    return renderSprite.getScale();
}

const sf::FloatRect& Clickable::getGlobalBounds() const
{
    return renderSprite.getGlobalBounds();
}

Clickable::Type Clickable::getType() const
{
    return type;
}

const sf::Sprite& Clickable::getSprite() const
{
    return renderSprite;
}

const sf::Texture& Clickable::getTexture() const
{
    return renderTexture.getTexture();
}


void Clickable::setPosition(const sf::Vector2f& newPosition)
{
    renderSprite.setPosition(newPosition);
}

void Clickable::setPosition(float x, float y)
{
    renderSprite.setPosition(x, y);
}

void Clickable::move(const sf::Vector2f& offset)
{
    renderSprite.move(offset);
}

void Clickable::move(float offsetX, float offsetY)
{
    renderSprite.move(offsetX, offsetY);
}

void Clickable::setRotation(float angle)
{
    renderSprite.setRotation(angle);
}

void Clickable::setSize(const sf::Vector2f& newSize)
{
    renderSprite.setScale(newSize.x / size.x, newSize.y / size.y);
}

void Clickable::setSize(float width, float height)
{
    renderSprite.setScale(width / size.x, height / size.y);
}

void Clickable::setOrigin(const sf::Vector2f& newOrigin)
{
    renderSprite.setOrigin(newOrigin.x, newOrigin.y);
}

void Clickable::setOrigin(float x, float y)
{
    renderSprite.setOrigin(x, y);
}

void Clickable::setScale(const sf::Vector2f& newScale)
{
    renderSprite.setScale(newScale.x, newScale.y);
}

void Clickable::setScale(float factorX, float factorY)
{
    renderSprite.setScale(factorX, factorY);
}

void Clickable::setScale(float factor)
{
    renderSprite.setScale(factor, factor);
}
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
