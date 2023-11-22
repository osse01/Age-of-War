#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <vector>
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
        void handleEvent();
        void draw(int, std::shared_ptr<sf::RenderWindow>, int);
        int buttonClicked(int, float, float);


    private:
    //  VARIABLES
        unsigned int    buttonSize;
        std::string     fontFile;
        std::string     interfaceFile;
        std::string     coinFile;

        std::vector<sf::RectangleShape> menuButtons;
        std::vector<sf::RectangleShape> gameButtons;

        sf::RectangleShape  interface;
        sf::RectangleShape  statsInterface;
        sf::Texture         interfaceTexture;
        sf::Texture         coinTexture;
        sf::Sprite          coinSprite;
        sf::Font            font;
        sf::Text            goldText;
};

#endif