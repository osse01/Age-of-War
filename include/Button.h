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
        Button(sf::Vector2f const, sf::Vector2f const, sf::Color const, sf::Color const, std::string const, sf::Font&);
        Button(sf::Vector2f const, sf::Vector2f const, sf::Sprite& , sf::Color const, bool=true, bool = false, float = 0);
        Button(sf::Vector2f const, sf::Vector2f const, sf::Color const);

        //Button(sf::RectangleShape, sf::Sprite, std::string="");
        ~Button() = default;

    //  FUNCTIONS
    sf::FloatRect getGlobalBounds  ();
    sf::Vector2f  getPosition      ();
    bool          click            ();
    sf::Sprite&   draw             ();
    void          hover            ();
    void          stopHover        ();
    void          setPosition      ( float , float = 0.0f );
    void          setCooldown      ( float );
    bool          hasAbility       ();
    void          updateCooldown   (std::shared_ptr<sf::Time>);



    private:
    //  VARIABLES
    int   i;
    bool  clicked;
    bool  hasCooldown;
    float cooldown;
    sf::RectangleShape                   button;
    std::shared_ptr<sf::Text>            text;
    sf::Sprite                           sprite;
    std::shared_ptr<sf::RenderTexture>   renderButton;
    sf::Sprite                           buttonSprite;
    sf::Color                            fillColor;
};
#endif