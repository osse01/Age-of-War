#include "../include/CreditsState.h"

CreditsState::CreditsState(std::shared_ptr<sf::RenderWindow> window,
     std::shared_ptr<sf::Music> gameMusic, std::shared_ptr<sf::Time> frameDuration)
//  ---------------------------------------------
:   State(window, gameMusic, frameDuration), nextState{ CREDITS_STATE }, elapsedTime{ 0 },
    nameList{}, nameFont{}, textFont{}, backgroundTexture{}, backgroundSprite{}, canvas{}, canvasSprite{}
{
    //  Load background image
    if(!backgroundTexture.loadFromFile("assets/background.jpeg"))
    {
        throw std::logic_error("    >> Error: Could Not Find credits image."
         "Error in CreditsState::CreditsState().");
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(window->getSize().x /backgroundSprite.getGlobalBounds().width,
    window->getSize().y /backgroundSprite.getGlobalBounds().height);
    
    //  Load fonts
    if(!(nameFont.loadFromFile("assets/royalFont.ttf") && textFont.loadFromFile("assets/newFont.ttf")))
    {
        throw std::logic_error("    >> Error: Could Not Find font file(s)."
         "Error in CreditsState::CreditsState().");
    }
    
    //  Set up Vector of Contributors
    const std::vector<std::string> stringList {"Oskar Bollner", "Logan Eriksson", 
    "Adam Hallberg", "Oscar Jemsson", "Johanna Nilsson", "Filip Ripstrand"};
    for ( auto &name : stringList)
    {
        nameList.push_back(sf::Text{name, nameFont, 50});
    }

    //  Setup canvas
    if(!canvas.create(window->getSize().x, window->getSize().y*12))
    {
        throw std::logic_error("    >> Error: Could not create sf::RenderTexture canvas."
         "Error in CreditsState::CreditsState().");
    }
    setupCanvas();

}

CreditsState::~CreditsState()
//  ---------------------------------------------
{}

void CreditsState::setupCanvas()
//  ---------------------------------------------
{
    sf::Text header{"Credits", textFont, 150};
    header.setPosition(canvas.getSize().x/2, window->getSize().y);
    header.setColor(sf::Color(255, 255, 255));
    header.setOrigin(header.getGlobalBounds().width/2, header.getGlobalBounds().height/2 );

    canvas.draw(header);

    for (unsigned i{}; i < nameList.size(); i++)
    {
        nameList.at(i).setPosition(canvas.getSize().x/2, window->getSize().y *(1.5 + 0.3*i));
        nameList.at(i).setColor(sf::Color(255, 255, 255));
        nameList.at(i).setOrigin(nameList.at(i).getGlobalBounds().width/2, nameList.at(i).getGlobalBounds().height/2 );

        canvas.draw(nameList.at(i));
    }
    canvas.display();

    canvasSprite.setTexture(canvas.getTexture());
}

int CreditsState::getNextState()
//  ---------------------------------------------
{
    return nextState;
}

void CreditsState::updateLogic()
//  ---------------------------------------------
{}

void CreditsState::resetState()
//  ---------------------------------------------
{
    elapsedTime = 0;
    nextState   = CREDITS_STATE;
}

void CreditsState::handleEvent(sf::Event event)
//  ---------------------------------------------
{
    switch(event.type)
        {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::F10:
                    nextState = MENU_STATE;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
        }
}

void CreditsState::renderFrame()
//  ---------------------------------------------
{   
    elapsedTime += frameDuration->asSeconds();
    window->clear(sf::Color(5, 0, 43));

    backgroundSprite.setPosition(backgroundSprite.getGlobalBounds().left,
        backgroundSprite.getGlobalBounds().top - 40 * frameDuration->asSeconds()); // Make slower later
    
    canvasSprite.setPosition(backgroundSprite.getGlobalBounds().left,
        backgroundSprite.getGlobalBounds().top - 30 * frameDuration->asSeconds());


    window->draw(backgroundSprite);
    window->draw(canvasSprite);
}
