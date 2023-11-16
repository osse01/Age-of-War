#include "../include/GUI.h"

#include <iostream>


GUI::GUI(int currentState, sf::RenderWindow* window)
    : buttonSize {window->getSize().x/20}, interface {sf::Vector2f(19*buttonSize/2.f, 2*buttonSize)}, menuButtons {}, gameButtons {}
{
    switch (currentState)
    {
    case MENU_STATE:
        {
           for (int i{0} ; i < 3 ; i++)
            {
                sf::RectangleShape button {sf::Vector2f(3*buttonSize, buttonSize)};
                button.setFillColor(sf::Color(0, 50*i, 50*i));
                button.setOrigin(button.getSize().x/2, 0);
                button.setPosition(window->getSize().x/2, window->getSize().y/2 + i * 1.1*buttonSize);
                menuButtons.push_back(button);
            }
            break;
        }

    case GAME_STATE:
        {
            interface.setPosition(window->getSize().x - interface.getSize().x, 0.f);
            interface.setOutlineThickness(5.f);
            interface.setOutlineColor(sf::Color(0, 0, 0));

            for (int i{0} ; i < 6 ; i++)
            {
                sf::RectangleShape button {sf::Vector2f(buttonSize, buttonSize)};
                button.setFillColor(sf::Color(0, 50*i, 50*i));
                button.setPosition(window->getSize().x - 3*buttonSize/2 - i * 3*buttonSize/2, buttonSize/2);
                gameButtons.push_back(button);
            }
            break;
        }
    default:
        break;
    }
    
}

void GUI::draw(int currentState, sf::RenderWindow* window)
{
    switch (currentState)
    {
        case MENU_STATE:
        {
            for (int i{0} ; i < 3 ; i++)
            {
                window->draw(menuButtons.at(i));
            }
            break;
        }
        case GAME_STATE:
            window->draw(interface);
            for (int i{0} ; i < 6 ; i++)
            {
                window->draw(gameButtons.at(i));
            }
            break;
        default:
            break; 
    }
    
}

int GUI::buttonClicked(int currentState, float mouseX, float mouseY)
{
    switch (currentState)
    {
        case MENU_STATE:
        {
            for (int i{0} ; i < 3 ; i++)
                {
                    if (menuButtons.at(i).getGlobalBounds().contains(mouseX,mouseY))
                    {
                        return i+1;
                    }
                }
            break;
        }
        case GAME_STATE:
        {
            for (int i{0} ; i < 6 ; i++)
                {
                    if (gameButtons.at(i).getGlobalBounds().contains(mouseX,mouseY))
                    {
                        return i+1;
                    }
                }
            break;
        }
        default:
            break;
    }
    return 0;
}