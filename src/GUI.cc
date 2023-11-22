#include "../include/GUI.h"

#include <iostream>


GUI::GUI(int currentState, std::shared_ptr<sf::RenderWindow> window)
    : buttonSize { window->getSize().x/30 }, fontFile{ "assets/newFont.ttf" },
      interfaceFile{ "assets/interfaceBackground.jpeg" },
      coinFile{ "assets/gameCoin.png" }, heartFile{ "assets/health.png" },
      menuButtons {}, gameButtons {}, interface { sf::Vector2f(19*buttonSize/2.f, 2*buttonSize) },
      statsInterface { sf::Vector2f(7*buttonSize/2.f, 2*buttonSize) },
      interfaceTexture{}, coinTexture{}, heartTexture{}, coinSprite{},
      heartSprite{}, font{}, goldText{}
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
                
                statsInterface.setPosition(0.f, 0.f);
                statsInterface.setOutlineThickness(2.f);
                statsInterface.setOutlineColor(sf::Color(0, 0, 0));
                statsInterface.setTexture(&interfaceTexture);
            }
            else
            {
                throw std::logic_error("\n  >> Error. Could not load interfaceBackground file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>)");
            }

            if ( coinTexture.loadFromFile(coinFile) && heartTexture.loadFromFile(heartFile))
            {
                coinSprite.setTexture(coinTexture);
                coinSprite.setScale(0.0025*buttonSize, 0.0025*buttonSize);

                heartSprite.setTexture(heartTexture);
                heartSprite.setScale(0.00083*buttonSize, 0.000833*buttonSize);

            }
            else
            {
                throw std::logic_error("\n  >> Error. Could not load coin or heart icon file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>)");
            }

            if ( font.loadFromFile(fontFile) )
            {
                goldText.setFont(font);
                goldText.setCharacterSize(buttonSize*0.4);
                goldText.setColor(sf::Color::Yellow);
            }
            else
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>)");
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
            window->draw(statsInterface);
            for (int i{0} ; i < 6 ; i++)
            {
                coinSprite.setPosition(0.5*buttonSize, 0.5*buttonSize);
                heartSprite.setPosition(0.5*buttonSize, 0.5*buttonSize + coinSprite.getGlobalBounds().height);


                goldText.setString(std::to_string(gold));
                goldText.setPosition(0.5*buttonSize + coinSprite.getGlobalBounds().width, 0.5*buttonSize);

                window->draw(goldText);
                window->draw(coinSprite);
                window->draw(heartSprite);
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