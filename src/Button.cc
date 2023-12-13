#include "../include/Button.h"

#include <iostream>

// Constructor for Button without Sprite
//This is a button with text
Button::Button( const sf::Vector2f buttonSize, sf::Vector2f pos,
                sf::Color fillColor, sf::Color outlineColor, 
                std::string buttonText, sf::Font& font )
:
    // Data Member Initialization List
    //---------------------------------------------------------------
    renderButton    { std::make_shared<sf::RenderTexture>()        }, 
    text            { std::make_shared<sf::Text>(buttonText, font) }, 
    button          { sf::RectangleShape(buttonSize)               },

    timer           {},
    buttonSprite    {},
    sprite          {},

    fillColor       { sf::Color(112, 58, 7) },

    currentCooldown { 0 },
    cooldown        { 0 },
    i               { 0 },

    hasCooldown     { false }, 
    clicked         { false }
    //---------------------------------------------------------------
{
    // Set Button Appearance and Position
    button.setFillColor (fillColor);
    button.setOutlineColor(outlineColor);
    button.setOutlineThickness(2.0f);
    button.setOrigin(button.getSize().x/2-2, button.getSize().y/2-2);
    button.setPosition(buttonSize.x/2, buttonSize.y/2);

    // Add Text to Button
    text->setFillColor(sf::Color::Black);
    text->setCharacterSize( static_cast<int>(0.6*buttonSize.y) );
    text->setOrigin(text->getGlobalBounds().width/2+2, 
                    text->getGlobalBounds().height/2 - 2);
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
// This is a button with a sprite
Button::Button( const sf::Vector2f buttonSize, sf::Vector2f pos,
                sf::Sprite& sprite, sf::Color fillColor, 
                bool clicked, bool ability, float cd )
:
    // Data Member Initialization List
    //----------------------------------------------------------
    renderButton    { std::make_shared<sf::RenderTexture>() },

    text            {}, 

    button          { sf::RectangleShape(buttonSize) },
    timer           { sf::RectangleShape(button)     }, 

    buttonSprite    {},

    sprite          { sprite    },
    fillColor       { fillColor },
    currentCooldown { cooldown  },
    cooldown        { cd        }, 

    i               { 1 }, 

    hasCooldown     { ability },
    clicked         { clicked } 
    //----------------------------------------------------------
{
    renderButton->create(buttonSize.x + 4, buttonSize.y + 4);

    // Set Button Appearance and Position
    button.setFillColor(fillColor);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2.0f);
    button.setOrigin(button.getSize().x/2, button.getSize().y/2);
    button.setPosition(buttonSize.x/2 + 2, buttonSize.y/2 + 2);

    // Set Sprite Position
    Button::sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
    Button::sprite.setPosition(buttonSize.x/2 + 2, buttonSize.y/2 + 2);
    Button::sprite.scale(renderButton->getSize().x/Button::sprite.getGlobalBounds().width, renderButton->getSize().y/Button::sprite.getGlobalBounds().height);

    // Set cooldown
    if (hasCooldown)
    {
        timer.setOrigin(timer.getGlobalBounds().width/2, timer.getGlobalBounds().height );
        timer.setFillColor(sf::Color(190, 190, 190, 200));
        timer.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y + button.getGlobalBounds().height/2 - 2));

    }

    // Create Button
    renderButton->clear(sf::Color::White);
    renderButton->draw(button);
    renderButton->draw(Button::sprite);
    if (hasCooldown)  {renderButton->draw(timer);}
    renderButton->display();

    //Create Sprite with Button
    buttonSprite.setTexture(renderButton->getTexture());
    buttonSprite.setOrigin(0,0);
    buttonSprite.setPosition(pos);
}

// Constructor for Button with Sprite
// This is a button with no sprite
Button::Button( const sf::Vector2f buttonSize,
                      sf::Vector2f pos, 
                      sf::Color    fillColor)
:
    // Data Member Initialization Lists
    //---------------------------------------------------------------

    renderButton    { std::make_shared<sf::RenderTexture>() },
    text            {},
    button          { sf::RectangleShape(buttonSize) }, 

    timer           {},
    buttonSprite    {},
    sprite          {},

    fillColor       { fillColor },    

    currentCooldown { 0 },
    cooldown        { 0 }, 
    i               { 2 }, 

    hasCooldown     { false },
    clicked         { false }
    //---------------------------------------------------------------
{
    renderButton->create(buttonSize.x+4, buttonSize.y+4);

    button.setFillColor(fillColor);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2.0f);
    button.setOrigin(button.getSize().x/2, button.getSize().y/2);
    button.setPosition(buttonSize.x/2+2, buttonSize.y/2+2);

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

bool Button::click()
{
    clicked = !clicked;
    if (clicked)
    {
        button.setFillColor(sf::Color(204, 107, 16));
    }
    else
    {
        button.setFillColor(sf::Color(112, 58, 7));
    }
    return clicked;
}
sf::Sprite& Button::draw(float coolDown)
{
    renderButton->clear(sf::Color::White);
    renderButton->draw(button);
    
    if (i==1 && clicked)
    {
        renderButton->draw(sprite);
    }
    else if (i==0)
    {
        renderButton->draw(*text);
    }
    
    if (hasCooldown)
    {
        setCooldown(coolDown);
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
    button.setFillColor(fillColor); 
}

void Button::setPosition(float xpos, float)
// Update position
{
    buttonSprite.setPosition(xpos, buttonSprite.getPosition().y);
}

void Button::setCooldown(float currentCooldown)
//  ---------------------------------------------
//  Create a Gray Transparrent Rectangle on the 
//  Button that Covers current cooldown / tot cooldown
//  of the Button.
//  ---------------------------------------------
{
    timer.setScale(1, (currentCooldown/cooldown));
    renderButton->draw(timer);
}



bool Button::hasAbility()
//  ---------------------------------------------
//  Returns if Button has Ability or Not.
//  ---------------------------------------------
{
    return hasCooldown;
}

void Button::updateCooldown(std::shared_ptr<sf::Time> frameDuration)
//  ---------------------------------------------
//  Reduce currentCooldown.
//  ---------------------------------------------
{
    (currentCooldown <= 0) ? currentCooldown = 0 : currentCooldown -= frameDuration->asSeconds();
}