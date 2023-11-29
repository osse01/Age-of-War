#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "State.h"


class GUI
{
    // -----------------------------------------------------------------
    // A class that handles buttons and graphics for the user interface.
    // -----------------------------------------------------------------

    public:
    //  CONSTRUCTORS
        GUI(int, std::shared_ptr<sf::RenderWindow>);
        ~GUI() = default;
        GUI(const GUI&) = delete;
        GUI& operator=(GUI&) = delete;

    //  FUNCTIONS
        void updateLogic(std::shared_ptr<sf::RenderWindow>);
        void draw(int, std::shared_ptr<sf::RenderWindow>, int=0);
        int buttonClicked(int, float, float);


    protected:
    //  VARIABLES
        unsigned int    buttonSize;
        std::string     fontFile;
        std::string     interfaceFile;
        std::string     coinFile;
        std::string     heartFile;

        std::vector<std::shared_ptr<Button>> menuButtons;
        std::vector<std::shared_ptr<Button>> gameButtons;
        std::vector<std::string>             menuTexts;


        sf::RectangleShape  interface;
        sf::RectangleShape  statsInterface;
        sf::RectangleShape  healthBar;
        sf::Texture         interfaceTexture;
        sf::Texture         coinTexture;
        sf::Texture         heartTexture;
        sf::Sprite          coinSprite;
        sf::Sprite          heartSprite;
        sf::Font            font;
        sf::Text            goldText;
        sf::Text            playText;
        sf::Text            optionsText;
        sf::Text            creditsText;
        sf::Text            quitText;

};

#endif