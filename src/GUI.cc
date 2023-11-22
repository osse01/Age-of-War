#include "../include/GUI.h"

#include <iostream>


GUI::GUI(int currentState, std::shared_ptr<sf::RenderWindow> window)
    : buttonSize { window->getSize().x/30 }, fontFile{ "assets/newFont.ttf" },
      interfaceFile{ "assets/interfaceBackground.jpeg" }, menuButtons {}, gameButtons {},
      interface { sf::Vector2f(19*buttonSize/2.f, 2*buttonSize) }, interfaceTexture{},
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
            if ( interfaceTexture.loadFromFile(interfaceFile) )
            {
                interface.setPosition(window->getSize().x - interface.getSize().x, 0.f);
                interface.setOutlineThickness(2.f);
                interface.setOutlineColor(sf::Color(0, 0, 0));
                interface.setTexture(&interfaceTexture);  
            }
            else
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>, int)");
            }

            if ( font.loadFromFile(fontFile) )
            {
                goldText.setFont(font);
                goldText.setCharacterSize(buttonSize*0.4);
                goldText.setColor(sf::Color::Yellow);
                goldText.setPosition(window->getSize().x - interface.getSize().x - 3*goldText.getGlobalBounds().width, 0.f);

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

void GUI::draw(int currentState, std::shared_ptr<sf::RenderWindow> window, int gold = 0)
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
                goldText.setString(std::to_string(gold));
                goldText.setPosition(window->getSize().x - interface.getSize().x - goldText.getGlobalBounds().width
                 - 0.15*buttonSize, 0.f);

                window->draw(goldText);
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