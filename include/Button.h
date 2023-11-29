#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "memory"


class Button
// -----------------------------------------------------------------
// A class that creates a Button.
// Use getButton() to get a drawable object.
//-----------------------------------------------------------------
{
    public:
    //  CONSTRUCTORS
        Button(sf::Vector2f, sf::Vector2f, sf::Color, sf::Color, std::string,sf::Font&);
        Button(sf::Vector2f, sf::Vector2f, sf::Sprite&, sf::Color);


        //Button(sf::RectangleShape, sf::Sprite, std::string="");
        ~Button() = default;

    //  FUNCTIONS
    sf::FloatRect getGlobalBounds();
    sf::Sprite&  draw();
    void         hover();
    void         stopHover();


    private:
    //  VARIABLES
    int i;
    sf::RectangleShape                   button;
    std::shared_ptr<sf::Text>            text;
    sf::Sprite                           sprite;
    std::shared_ptr<sf::RenderTexture>   renderButton;
    sf::Sprite                           buttonSprite;
};
#endif