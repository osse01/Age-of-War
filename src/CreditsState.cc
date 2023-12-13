#include "../include/CreditsState.h"

CreditsState::CreditsState( std::shared_ptr<sf::RenderWindow> window,
                            FileReader::Data& dataMap,
                            std::shared_ptr<sf::Music> gameMusic,
                            std::map<std::string, 
                            std::shared_ptr<sf::Sound>> sound, 
                            std::shared_ptr<sf::Time> frameDuration)
:   
    // Data Member Initialization List
    //---------------------------------------------------------------
    State(window, dataMap, gameMusic, sound, frameDuration),

    nameList            {},
    canvas              {},
    backgroundTexture   {},
    fadeTexture         {},
    backgroundSprite1   {}, 
    backgroundSprite2   {},
    canvasSprite        {},
    fadeSprite          {},
    nameFont            {},
    textFont            {},

    elapsedTime         { 0 },
    nextState           { CREDITS_STATE }
    //---------------------------------------------------------------
{
    // Load Background Image
    if(!backgroundTexture.loadFromFile(dataMap.files["Background"]))
    {
        throw std::logic_error("    >> Error: Could Not Find credits image."
         "Error in CreditsState::CreditsState().");
    }
    backgroundSprite1.setTexture(backgroundTexture);
    backgroundSprite1.setScale(window->getSize().x /backgroundSprite1.getGlobalBounds().width,
    window->getSize().y /backgroundSprite1.getGlobalBounds().height);
    backgroundSprite2.setTexture(backgroundTexture);
    backgroundSprite2.setScale(window->getSize().x /backgroundSprite2.getGlobalBounds().width,
    window->getSize().y /backgroundSprite2.getGlobalBounds().height);
    
    // Load Fonts
    if(!(nameFont.loadFromFile(dataMap.files["CreditFont"]) && textFont.loadFromFile(dataMap.files["GameFont"])))
    {
        throw std::logic_error("    >> Error: Could Not Find font file(s)."
         "Error in CreditsState::CreditsState().");
    }

    //  Load gradient
    if(!(fadeTexture.loadFromFile(dataMap.files["CreditsFade"]) ))
    {
        throw std::logic_error("    >> Error: Could Not Find gradient."
         "Error in CreditsState::CreditsState().");
    }
    fadeSprite.setTexture(fadeTexture);
    
    // Setup Vector of Contributors
    const std::vector<std::string> stringList {"Oskar Bollner", "Logan Eriksson", 
    "Adam Hallberg", "Oscar Jemsson", "Johanna Nilsson", "Filip Ripstrand", "Eric Ekstrom", "Tim Lundqvist"};
    for ( auto &name : stringList)
    {
        nameList.push_back(sf::Text{name, nameFont, 50});
    }


    // Setup Canvas
    setupCanvas();
}

CreditsState::~CreditsState()
//  ---------------------------------------------
{}

void CreditsState::setupCanvas()
//  ---------------------------------------------
{
    canvas.create(window->getSize().x, window->getSize().y *(4) + fadeSprite.getGlobalBounds().height );    

    // Set Header Appearance and Position
    sf::Text header{"Credits", nameFont, 150};
    header.setOrigin(header.getGlobalBounds().width/2, header.getGlobalBounds().height/2 );
    header.setPosition(canvas.getSize().x/2, window->getSize().y);
    header.setFillColor(sf::Color(255, 255, 255));

    canvas.draw(header);

    //  Setup fadein to Menu
    fadeSprite.setOrigin(fadeSprite.getGlobalBounds().width/2, fadeSprite.getGlobalBounds().height);
    fadeSprite.setPosition(canvas.getSize().x/2, canvas.getSize().y - backgroundSprite1.getGlobalBounds().height);
    canvas.draw(fadeSprite);

    // Set Position and Color for Names of Main contributers
    for (unsigned i{}; i < nameList.size()-2; i++)
    {
        nameList.at(i).setPosition(canvas.getSize().x/2, window->getSize().y *(1.5 + 0.25*i));
        nameList.at(i).setFillColor(sf::Color(255, 255, 255));
        nameList.at(i).setOrigin(nameList.at(i).getGlobalBounds().width/2, nameList.at(i).getGlobalBounds().height/2 );

        canvas.draw(nameList.at(i));
    }

    //  Special contributers
    sf::Text second_header{"Special Thanks", nameFont, 150};
    second_header.setOrigin(second_header.getGlobalBounds().width/2, second_header.getGlobalBounds().height/2 );
    second_header.setPosition(canvas.getSize().x/2,  window->getSize().y *(1.5 + 0.25*6) );
    second_header.setFillColor(sf::Color(255, 255, 255));
    
    canvas.draw(second_header);

    // Set Position and Color for Names of Special contributers
    for (unsigned i{6}; i < nameList.size(); i++)
    {
        nameList.at(i).setPosition(canvas.getSize().x/2, window->getSize().y *(1.5 + 0.25*(i + 1)));
        nameList.at(i).setFillColor(sf::Color(255, 255, 255));
        nameList.at(i).setOrigin(nameList.at(i).getGlobalBounds().width/2, nameList.at(i).getGlobalBounds().height/2 );

        canvas.draw(nameList.at(i));
    }

    sf::Text header3{"Thanks for Playing!", nameFont, 150};
    header3.setOrigin(header3.getGlobalBounds().width/2, header3.getGlobalBounds().height/2 );
    header3.setPosition(canvas.getSize().x/2, window->getSize().y);
    header3.setFillColor(sf::Color(255, 255, 255));
    header3.setPosition(canvas.getSize().x/2, fadeSprite.getGlobalBounds().top + fadeSprite.getGlobalBounds().height/1.5 );
    canvas.draw(header3);

    //  Setup menu at end

    backgroundSprite2.setPosition(0, fadeSprite.getGlobalBounds().height + fadeSprite.getGlobalBounds().top );
    canvas.draw(backgroundSprite2);

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
{
    if ( window->getSize().y >= canvasSprite.getGlobalBounds().height + canvasSprite.getGlobalBounds().top  )
    {
        
        nextState = MENU_STATE;
    }
}

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
    backgroundSprite1.setPosition(backgroundSprite1.getGlobalBounds().left,
    backgroundSprite1.getGlobalBounds().top - 60 * frameDuration->asSeconds()); // Make slower later 40 första 30 andra orginal
    
    // Set Canvas Position
    canvasSprite.setPosition(backgroundSprite1.getGlobalBounds().left,
    backgroundSprite1.getGlobalBounds().top - 60 * frameDuration->asSeconds());
    
    // Draw Sprites
    window->draw(backgroundSprite1);
    window->draw(canvasSprite);
}