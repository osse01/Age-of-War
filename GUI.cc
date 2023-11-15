#include "GUI.h"

#include <iostream>

GUI::GUI(int currentState, sf::RenderWindow* window)
    : interface {sf::Vector2f(1000.f, 200.f)}, buttons {}
{
    interface.setPosition(window->getSize().x - 1000.f, 0);
    interface.setOutlineThickness(5.f);
    interface.setOutlineColor(sf::Color(0, 0, 0));

    for (int i{0} ; i < 6 ; i++)
    {
        sf::RectangleShape button {sf::Vector2f(100.f,100.f)};
        button.setFillColor(sf::Color(50*i, 50*i, 50*i));
        button.setPosition(window->getSize().x - 150 - i * 150, 50);
        buttons.push_back(button);
    }
}

void GUI::draw(sf::RenderWindow* window)
{
    window->draw(interface);
    for (int i{0} ; i < 6 ; i++)
    {
        window->draw(buttons.at(i));
    }
}

int GUI::buttonClicked(float mouseX, float mouseY)
{
    for (int i{0} ; i < 6 ; i++)
    {
        if (buttons.at(i).getGlobalBounds().contains(mouseX,mouseY))
        {
            return i+1;
        }
    }
}