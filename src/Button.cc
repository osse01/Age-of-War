#include "../include/Button.h"

#include <iostream>


Button::Button(const sf::Vector2f buttonSize, sf::Vector2f pos, sf::Color fillColor, sf::Color outlineColor, std::string buttonText, sf::Font& font)
//This is a button with text
: i {0}, button { sf::RectangleShape(buttonSize) }, text {std::make_shared<sf::Text>(buttonText, font)}, sprite {},
  renderButton {std::make_shared<sf::RenderTexture>()}, buttonSprite {}, fillColor {sf::Color(112, 58, 7)}
{
    button.setFillColor(fillColor);
    button.setOutlineColor(outlineColor);
    button.setOutlineThickness(2.0f);
    button.setOrigin(button.getSize().x/2-2, button.getSize().y/2-2);
    button.setPosition(buttonSize.x/2, buttonSize.y/2);


    text->setFillColor(sf::Color::Black);
    text->setOrigin(text->getGlobalBounds().width/2+2, text->getGlobalBounds().height/2 - 2);
    text->setPosition(button.getPosition());

    renderButton->create(buttonSize.x+4, buttonSize.y+4);
    renderButton->clear(sf::Color::White);
    renderButton->draw(button);
    renderButton->draw(*text);
    renderButton->display();

    buttonSprite.setTexture(renderButton->getTexture());
    buttonSprite.setOrigin(buttonSize.x/2+2, buttonSize.y/2+2);
    buttonSprite.setPosition(pos);
}

Button::Button(const sf::Vector2f buttonSize, sf::Vector2f pos, sf::Sprite& sprite, sf::Color fillColor)
// This is a button with a sprite
: i {1}, button { sf::RectangleShape(buttonSize) }, text {}, sprite { sprite },
  renderButton {std::make_shared<sf::RenderTexture>()}, buttonSprite {}, fillColor { fillColor }
{
    renderButton->create(buttonSize.x + 4, buttonSize.y + 4);

    button.setFillColor(fillColor);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2.0f);
    button.setOrigin(button.getSize().x/2-2, button.getSize().y/2-2);
    button.setPosition(buttonSize.x/2, buttonSize.y/2);


    Button::sprite.setOrigin(sprite.getGlobalBounds().width/2 + 4, sprite.getGlobalBounds().height/2 + 2);
    Button::sprite.setPosition(button.getPosition());
    Button::sprite.scale(renderButton->getSize().x/Button::sprite.getGlobalBounds().width, renderButton->getSize().y/Button::sprite.getGlobalBounds().height);

    renderButton->clear(sf::Color::White);
    renderButton->draw(button);
    renderButton->draw(Button::sprite);
    renderButton->display();

    buttonSprite.setTexture(renderButton->getTexture());
    buttonSprite.setOrigin(0,0);
    buttonSprite.setPosition(pos);
}

Button::Button(const sf::Vector2f buttonSize, sf::Vector2f pos, sf::Color fillColor)
// This is a button with no sprite
: i {2}, button { sf::RectangleShape(buttonSize) }, text {}, sprite {},
  renderButton {std::make_shared<sf::RenderTexture>()}, buttonSprite {}, fillColor {fillColor}
{
    renderButton->create(buttonSize.x, buttonSize.y);

    button.setFillColor(fillColor);
    button.setOrigin(button.getSize().x/2, button.getSize().y/2);
    button.setPosition(buttonSize.x/2, buttonSize.y/2);

    renderButton->clear(sf::Color::White);
    renderButton->draw(button);
    renderButton->display();

    buttonSprite.setTexture(renderButton->getTexture());
    buttonSprite.setOrigin(button.getOrigin());
    buttonSprite.setPosition(pos);
}


sf::FloatRect Button::getGlobalBounds()
{
    return buttonSprite.getGlobalBounds();
}

sf::Vector2f Button::getPosition()
{
    return buttonSprite.getPosition();
}

sf::Sprite& Button::draw()
{
    renderButton->clear(sf::Color::White);

    renderButton->draw(button);
    
    if (i==1)
    {
    renderButton->draw(sprite);
    }
    else if (i==0)
    {
        renderButton->draw(*text);

    }

    renderButton->display();
    
    buttonSprite.setTexture(renderButton->getTexture());
    
    
    return buttonSprite;
}

void Button::hover()
// Change color when hovering
{
    button.setFillColor(sf::Color(204, 107, 16));
}

void Button::stopHover()
// Change back to the original color.
{
    button.setFillColor(fillColor); 
}

void Button::updatePosition(float xpos)
// Update position
{
    buttonSprite.setPosition(xpos, buttonSprite.getPosition().y);
}
