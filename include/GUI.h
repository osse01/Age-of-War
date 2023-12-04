#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "State.h"
#include "FileReader.h"

class GUI
{
    // -----------------------------------------------------------------
    // A class that handles buttons and graphics for the user interface.
    // -----------------------------------------------------------------

    public:
    //  CONSTRUCTORS
        GUI(int, std::shared_ptr<sf::RenderWindow>, FileReader::Data&);
        ~GUI() = default;
        GUI(const GUI&) = delete;
        GUI& operator=(GUI&) = delete;

    //  FUNCTIONS
        void updateLogic(std::shared_ptr<sf::RenderWindow>, int);
        void draw(int, std::shared_ptr<sf::RenderWindow>, int=0);
        void drawHPBar(std::shared_ptr<sf::RenderWindow>, const sf::Sprite&,  int, int);
        int buttonClicked(int, float, float);
        void setBaseHP(int);


    protected:
    //  VARIABLES
        unsigned int     buttonSize;
        unsigned int     originalBaseHP;
        FileReader::Data dataMap;
        std::string      heartFile;

        std::vector<std::shared_ptr<Button>> menuButtons;
        std::vector<std::shared_ptr<Button>> gameButtons;
        std::vector<std::string>             menuTexts;
        std::vector<sf::Texture>             gameTextures;


        sf::RectangleShape  interface;
        sf::RectangleShape  statsInterface;
        sf::RectangleShape  healthBar;
        sf::RectangleShape  enemyHealthBar;
        sf::RectangleShape  healthRec;
        sf::RectangleShape  enemyHealthRec;
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