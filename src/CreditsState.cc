#include "../include/CreditsState.h"

CreditsState::CreditsState(std::shared_ptr<sf::RenderWindow> window, FileReader::Data& dataMap,
     std::shared_ptr<sf::Music> gameMusic, std::map<std::string, std::shared_ptr<sf::Sound>> sound, std::shared_ptr<sf::Time> frameDuration)
//  ---------------------------------------------
:   State(window, dataMap, gameMusic, sound, frameDuration), nextState{ CREDITS_STATE }, elapsedTime{ 0 },
    nameList{}, nameFont{}, textFont{}, backgroundTexture{}, backgroundSprite{}, canvas{}, canvasSprite{}
{
    // Load Background Image
    if(!backgroundTexture.loadFromFile(dataMap.files["Background"]))
    {
        throw std::logic_error("    >> Error: Could Not Find credits image."
         "Error in CreditsState::CreditsState().");
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(window->getSize().x /backgroundSprite.getGlobalBounds().width,
    window->getSize().y /backgroundSprite.getGlobalBounds().height);
    
    // Load Fonts
    if(!(nameFont.loadFromFile(dataMap.files["CreditFont"]) && textFont.loadFromFile(dataMap.files["GameFont"])))
    {
        throw std::logic_error("    >> Error: Could Not Find font file(s)."
         "Error in CreditsState::CreditsState().");
    }
    
    // Setup Vector of Contributors
    const std::vector<std::string> stringList {"Oskar Bollner", "Logan Eriksson", 
    "Adam Hallberg", "Oscar Jemsson", "Johanna Nilsson", "Filip Ripstrand"};
    for ( auto &name : stringList)
    {
        nameList.push_back(sf::Text{name, nameFont, 50});
    }

    // Setup Canvas
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
    // Set Header Appearance and Position
    sf::Text header{"Credits", textFont, 150};
    header.setPosition(canvas.getSize().x/2, window->getSize().y);
    header.setFillColor(sf::Color(255, 255, 255));
    header.setOrigin(header.getGlobalBounds().width/2, header.getGlobalBounds().height/2 );

    canvas.draw(header);

    // Set Position and Color for Names
    for (unsigned i{}; i < nameList.size(); i++)
    {
        nameList.at(i).setPosition(canvas.getSize().x/2, window->getSize().y *(1.5 + 0.3*i));
        nameList.at(i).setFillColor(sf::Color(255, 255, 255));
        nameList.at(i).setOrigin(nameList.at(i).getGlobalBounds().width/2, nameList.at(i).getGlobalBounds().height/2 );

        canvas.draw(nameList.at(i));
    }
    canvas.display();

    canvasSprite.setTexture(canvas.getTexture());
}

int CreditsState::getNextState()
// ---------------------------------------------
// Return Next State
{
    return nextState;
}

void CreditsState::updateLogic()
//  ---------------------------------------------
{}

void CreditsState::resetState()
//  ---------------------------------------------
// Reset nextState variable to Credits State
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
                //Change State to Menu State
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

    //Set Background Position 
    backgroundSprite.setPosition(backgroundSprite.getGlobalBounds().left,
    backgroundSprite.getGlobalBounds().top - 40 * frameDuration->asSeconds()); // Make slower later
    
    // Set Canvas Position
    canvasSprite.setPosition(backgroundSprite.getGlobalBounds().left,
    backgroundSprite.getGlobalBounds().top - 30 * frameDuration->asSeconds());

    // Draw Sprites
    window->draw(backgroundSprite);
    window->draw(canvasSprite);
}