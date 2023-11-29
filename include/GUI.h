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
        void updateLogic(std::shared_ptr<sf::RenderWindow>, int);
        void draw(int, std::shared_ptr<sf::RenderWindow>, int, int);
        int buttonClicked(int, float, float);
        void setBaseHP(int);


    private:
    //  VARIABLES
        unsigned int    buttonSize;
        unsigned int    originalBaseHP;
        std::string     fontFile;
        std::string     interfaceFile;
        std::string     coinFile;
        std::string     heartFile;

        std::vector<sf::RectangleShape> menuButtons;
        std::vector<sf::RectangleShape> gameButtons;
        std::vector<sf::Text>           menuTexts;


        sf::RectangleShape  interface;
        sf::RectangleShape  statsInterface;
        sf::RectangleShape  healthBar;
        sf::RectangleShape  healthRec;
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

};

#endif