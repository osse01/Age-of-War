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
        GUI(int, sf::RenderWindow*);
        ~GUI() = default;
        GUI(const GUI&) = delete;
        GUI& operator=(GUI&) = delete;

    //  FUNCTIONS
        void handleEvent();
        void draw(int, sf::RenderWindow*);
        int buttonClicked(int, float, float);


    private:
    //  VARIABLES
        unsigned float buttonSize;
        sf::RectangleShape interface;
        std::vector<sf::RectangleShape> menuButtons;
        std::vector<sf::RectangleShape> gameButtons;
        
};

#endif