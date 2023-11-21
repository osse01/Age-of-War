#include "../include/GUI.h"

#include <iostream>


GUI::GUI(int currentState, std::shared_ptr<sf::RenderWindow> window, int gold)
    : buttonSize { window->getSize().x/20 }, fontFile{ "assets/newFont.ttf" }, 
      menuButtons {}, gameButtons {}, interface { sf::Vector2f(19*buttonSize/2.f, 2*buttonSize) },
      font{}, goldText{}
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

            if ( font.loadFromFile(fontFile) )
            {
                goldText.setFont(font);
                goldText.setString("qwerty9999rty");//std::to_string(gold)
                goldText.setCharacterSize(20);
                goldText.setColor(sf::Color::Cyan);
            }
            else
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>, int)");
            }

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

void GUI::draw(int currentState, std::shared_ptr<sf::RenderWindow> window)
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
                window->draw(goldText);
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