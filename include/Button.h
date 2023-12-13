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
    // CONSTRUCTORS / DESTRUCTORS
    Button( sf::Vector2f const, sf::Vector2f const, 
            sf::Color    const, sf::Color    const,
            std::string  const, sf::Font&);

    Button( sf::Vector2f const, sf::Vector2f const,
            sf::Sprite& , sf::Color const, 
            bool=true, bool = false, float = 0);

    Button( sf::Vector2f const, 
            sf::Vector2f const,
            sf::Color    const);

    ~Button() = default;

    // FUNCTIONS
    void          updateCooldown   ( std::shared_ptr<sf::Time> );

    void          setPosition      ( float , float = 0.0f );
    void          setCooldown      ( float );

    sf::Sprite&   draw             ( float = -1 );
    sf::FloatRect getGlobalBounds  ();
    sf::Vector2f  getPosition      ();

    void          hover            ();
    void          stopHover        ();
    bool          hasAbility       ();
    bool          click            ();

private:
    // VARIABLES
    std::shared_ptr<sf::RenderTexture>  renderButton;
    std::shared_ptr<sf::Text>           text;
    sf::RectangleShape                  button;
    sf::RectangleShape                  timer;
    sf::Sprite                          buttonSprite;
    sf::Sprite                          sprite;
    sf::Color                           fillColor;


    float                               currentCooldown;
    float                               cooldown;
    int                                 i;
    bool                                hasCooldown;
    bool                                clicked;
    
    


};

#endif