#include "../include/Button.h"

#include <iostream>

// Constructor for Button without Sprite
Button::Button(const sf::Vector2f buttonSize, sf::Vector2f pos, sf::Color fillColor, sf::Color outlineColor, std::string buttonText, sf::Font& font)
: i {0}, button { sf::RectangleShape(buttonSize) }, text {std::make_shared<sf::Text>(buttonText, font)}, sprite {},
  renderButton {std::make_shared<sf::RenderTexture>()}, buttonSprite {}
{
    // Set Button Appearance and Position
    button.setFillColor(fillColor);
    button.setOutlineColor(outlineColor);
    button.setOutlineThickness(2.0f);
    button.setOrigin(button.getSize().x/2-2, button.getSize().y/2-2);
    button.setPosition(buttonSize.x/2, buttonSize.y/2);

    // Add Text to Button
    text->setFillColor(sf::Color::Black);
    text->setOrigin(text->getGlobalBounds().width/2+2, text->getGlobalBounds().height/2 - 2);
    text->setPosition(button.getPosition());

    // Create Button
    renderButton->create(buttonSize.x+4, buttonSize.y+4);
    renderButton->clear(sf::Color::White);
    renderButton->draw(button);
    renderButton->draw(*text);
    renderButton->display();

    // Create Sprite with Button
    buttonSprite.setTexture(renderButton->getTexture());
    buttonSprite.setOrigin(buttonSize.x/2+2, buttonSize.y/2+2);
    buttonSprite.setPosition(pos);
}

// Constructor for Button with Sprite
Button::Button(const sf::Vector2f buttonSize, sf::Vector2f pos, sf::Sprite& sprite, sf::Color fillColor)
: i {1}, button { sf::RectangleShape(buttonSize) }, text {}, sprite { sprite },
  renderButton {std::make_shared<sf::RenderTexture>()}, buttonSprite {}
  {
    renderButton->create(buttonSize.x + 4, buttonSize.y + 4);

    // Set Button Appearance and Position
    button.setFillColor(fillColor);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2.0f);
    button.setOrigin(button.getSize().x/2-2, button.getSize().y/2-2);
    button.setPosition(buttonSize.x/2, buttonSize.y/2);

    // Set Sprite Position
    Button::sprite.setOrigin(sprite.getGlobalBounds().width/2 + 4, sprite.getGlobalBounds().height/2 + 2);
    Button::sprite.setPosition(button.getPosition());
    Button::sprite.scale(renderButton->getSize().x/Button::sprite.getGlobalBounds().width, renderButton->getSize().y/Button::sprite.getGlobalBounds().height);

    // Create Button
    renderButton->clear(sf::Color::White);
    renderButton->draw(button);
    renderButton->draw(Button::sprite);
    renderButton->display();

    //Create Sprite with Button
    buttonSprite.setTexture(renderButton->getTexture());
    buttonSprite.setOrigin(0,0);
    buttonSprite.setPosition(pos);
  }

// Return Global Bounds for Sprite
sf::FloatRect Button::getGlobalBounds()
{
    return buttonSprite.getGlobalBounds();
}

// Draw and Return Button Sprite
sf::Sprite& Button::draw()
{
    renderButton->clear(sf::Color::White);
    renderButton->draw(button);
    
    if (i)
    {
    renderButton->draw(sprite);
    }
    else
    {
    renderButton->draw(*text);
    }

    renderButton->display();
    buttonSprite.setTexture(renderButton->getTexture());
    return buttonSprite;
}

// Change Color when Hovering
void Button::hover()
{
    button.setFillColor(sf::Color(204, 107, 16));
}

// Change Back to the Original Color
void Button::stopHover()
{
    button.setFillColor(sf::Color(112, 58, 7)); 
}
