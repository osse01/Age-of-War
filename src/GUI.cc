#include "../include/GUI.h"
#include <iostream>
#include <cmath>

// Standard Button RGB Color: (112, 58, 7)

GUI::GUI(int currentState, std::shared_ptr<sf::RenderWindow> window, FileReader::Data& data)
    : buttonSize { window->getSize().x/30 }, originalBaseHP{data.stats["Base"]["hp"]}, dataMap{data}, heartFile{ "assets/health.png" },
      menuButtons {}, gameButtons {}, pausedButtons{}, optionsButtons {}, winButtons{}, loseButtons{},
      menuTexts{}, pausedTexts{}, winTexts{}, loseTexts{}, gameTextures {},
      interface { sf::Vector2f(19*buttonSize/2.f, 2*buttonSize) }, statsInterface { sf::Vector2f(7*buttonSize/2, 2*buttonSize) },
      healthBar{ sf::Vector2f(buttonSize/3, 6*buttonSize) }, enemyHealthBar{ healthBar },
      healthRec{ healthBar }, enemyHealthRec{ healthBar },
      interfaceTexture{}, coinTexture{}, heartTexture{}, checkTexture{}, coinSprite{}, heartSprite{}, checkSprite{}, font{}, goldText{}, optionsText{}
{
    // Add Textures to gameTextures
    sf::Texture tmpText {};
    tmpText.loadFromFile(dataMap.files["Cursor"]);
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile(dataMap.files["GameCoin"]);
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile("assets/health.png");
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile(dataMap.files["Trees"]);
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile("assets/friendly_" + dataMap.files["Ranged"]);
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile("assets/friendly_" + dataMap.files["Melee"]);
        gameTextures.push_back(tmpText);
    switch (currentState)
    {
    case MENU_STATE:
        {
            // Load Font
            if ( !font.loadFromFile(dataMap.files["GameFont"]) )
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                    "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) MENU_STATE");
            }
            // Add Texts for Buttons in Menu
            menuTexts.push_back("Start game");
            menuTexts.push_back("Options");
            menuTexts.push_back("Credits");
            menuTexts.push_back("Quit");

            // Create Menu Buttons
            for (int i{0} ; i < static_cast<int>(menuTexts.size()) ; i++)
            {
                menuButtons.push_back(std::make_shared<Button>(
                                            sf::Vector2f(3*buttonSize, buttonSize), 
                                            sf::Vector2f(window->getSize().x/2, window->getSize().y/2 + i * 1.2*buttonSize), 
                                            sf::Color(112, 58, 7), sf::Color::Black, menuTexts.at(i), font));
            }
            break;
        }
    case PAUSE_STATE:
        {
            // Load Font
            if ( !(font.loadFromFile(dataMap.files["GameFont"])) )
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) PAUSE_STATE");
            }
            // Add Texts for Buttons in Pause State
            pausedTexts.push_back("Resume Game");
            pausedTexts.push_back("Options");
            pausedTexts.push_back("Main Menu");

            // Create Pause Buttons
            for (long unsigned int i{0} ; i < pausedTexts.size() ; i++)
            {
                pausedButtons.push_back(std::make_shared<Button>(
                                            sf::Vector2f(3*buttonSize, buttonSize), 
                                            sf::Vector2f(window->getSize().x/2, window->getSize().y/2 + i * 1.2*buttonSize), 
                                            sf::Color(112, 58, 7), sf::Color::Black, pausedTexts.at(i), font));
            }
            break;
        }
    case WIN_STATE:
        {
            // Load Font
            if ( !(font.loadFromFile(dataMap.files["GameFont"])) )
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) PAUSED_STATE");
            }
            // Add Texts for Buttons in Win State
            winTexts.push_back("Main Menu");
            winTexts.push_back("Quit");
    
            // Create Win Buttons
            for (long unsigned int i{0} ; i < winTexts.size() ; i++)
            {
                winButtons.push_back(std::make_shared<Button>(
                                            sf::Vector2f(3*buttonSize, buttonSize), 
                                            sf::Vector2f(window->getSize().x/2, window->getSize().y/2 + i * 1.2*buttonSize), 
                                            sf::Color(112, 58, 7), sf::Color::Black, winTexts.at(i), font));
            }
            break;
        }
    case LOSE_STATE:
        {
            // Load Font
            if ( !(font.loadFromFile(dataMap.files["GameFont"])) )
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) PAUSED_STATE");
            }
            // Add Texts for Buttons in Lose State
            loseTexts.push_back("Main Menu");
            loseTexts.push_back("Quit");
    
            // Create Lose Buttons
            for (long unsigned int i{0} ; i < loseTexts.size() ; i++)
            {
                loseButtons.push_back(std::make_shared<Button>(
                                            sf::Vector2f(3*buttonSize, buttonSize), 
                                            sf::Vector2f(window->getSize().x/2, window->getSize().y/2 + i * 1.2*buttonSize), 
                                            sf::Color(112, 58, 7), sf::Color::Black, loseTexts.at(i), font));
            }
            break;
        }
    case GAME_STATE:
        {
        //  Set up Interface
            if ( !interfaceTexture.loadFromFile(dataMap.files["GUITexture"]) )
            {
                throw std::logic_error("\n  >> Error. Could not load interfaceBackground file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) GAME_STATE");
            }
            // Set Position and Appearance for Button Bar 
            interface.setPosition(window->getSize().x - interface.getSize().x, 0.f);
            interface.setOutlineThickness(2.f);
            interface.setOutlineColor(sf::Color(0, 0, 0));
            interface.setTexture(&interfaceTexture);
            
            // Set Position and Appearance for Stats Background
            statsInterface.setPosition(0.f, 0.f);
            statsInterface.setOutlineThickness(2.f);
            statsInterface.setOutlineColor(sf::Color(0, 0, 0));
            statsInterface.setTexture(&interfaceTexture);

            // Set Position and Appearance for Health Bar
            healthBar.setOrigin(0,healthBar.getGlobalBounds().height);
            healthBar.setPosition(buttonSize/2, 10*buttonSize);
            healthBar.setOutlineThickness(3.f);
            healthBar.setFillColor(sf::Color(109, 109, 110));
            healthBar.setOutlineColor(sf::Color(0, 0, 0));
            
            // Set Position and Appearance for Initial Health Bar
            healthRec.setOrigin(0,healthRec.getGlobalBounds().height);
            healthRec.setPosition(healthBar.getPosition().x, healthBar.getPosition().y);
            healthRec.setOutlineThickness(3.f);
            healthRec.setFillColor(sf::Color(200, 10, 0));
            healthRec.setOutlineColor(sf::Color(0, 0, 0));

            // Set Position and Appearance for Enemy Health Bar
            enemyHealthBar.setOrigin(0,enemyHealthBar.getGlobalBounds().height);
            enemyHealthBar.setPosition(buttonSize/2, 10*buttonSize);
            enemyHealthBar.setOutlineThickness(3.f);
            enemyHealthBar.setFillColor(sf::Color(109, 109, 110));
            enemyHealthBar.setOutlineColor(sf::Color(0, 0, 0));

            // Set Position and Appearance for Initial Enemy Health Bar
            enemyHealthRec.setOrigin(0,enemyHealthRec.getGlobalBounds().height);
            enemyHealthRec.setPosition(enemyHealthBar.getPosition().x, enemyHealthBar.getPosition().y);
            enemyHealthRec.setOutlineThickness(3.f);
            enemyHealthRec.setFillColor(sf::Color(200, 10, 0));
            enemyHealthRec.setOutlineColor(sf::Color(0, 0, 0));
            
            //  Set up Gold Information 
            if ( !(coinTexture.loadFromFile(dataMap.files["GameCoin"]) && heartTexture.loadFromFile(heartFile)))
            {
                throw std::logic_error("\n  >> Error. Could not load coin or heart icon file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) GAME_STATE");
            }
            coinSprite.setTexture(coinTexture);
            coinSprite.setScale(0.0025*buttonSize, 0.0025*buttonSize);

            heartSprite.setTexture(heartTexture);
            heartSprite.setScale(0.00083*buttonSize, 0.000833*buttonSize);

            if ( !font.loadFromFile(dataMap.files["GameFont"]) )
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) GAME_STATE");
            }

            goldText.setFont(font);
            goldText.setCharacterSize(buttonSize*0.4);
            goldText.setFillColor(sf::Color::Yellow);

            // Create Game Buttons
            for (int i{0} ; i < 6 ; i++)
            {
                sf::Sprite sprite {gameTextures.at(i)};
                if (i>3)
                {
                    sprite.setTextureRect(sf::IntRect(0,0,128,128));
                }
                gameButtons.push_back(std::make_shared<Button>(
                                            sf::Vector2f(buttonSize, buttonSize), 
                                            sf::Vector2f(window->getSize().x - 3*buttonSize/2 - i * 3*buttonSize/2, buttonSize/2), 
                                            sprite, sf::Color(112, 58, 7)));
            }
            break;
        }
    
    case OPTIONS_STATE:
        {
        if ( !(font.loadFromFile(dataMap.files["GameFont"])) )
        {
            throw std::logic_error("\n  >> Error. Could not load font file. "
            "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) OPTIONS_STATE");
        }
        if ( !interfaceTexture.loadFromFile(dataMap.files["GUITexture"]) )
        {
            throw std::logic_error("\n  >> Error. Could not load interfaceBackground file. "
            "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) OPTIONS_STATE");
        }
        if ( !checkTexture.loadFromFile(dataMap.files["check"]) )
        {
            throw std::logic_error("\n  >> Error. Could not load checkTexture file. "
            "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>) OPTIONS_STATE");
        }

        interface.setSize(sf::Vector2f(15*buttonSize, 8*buttonSize));
        interface.setOrigin(interface.getSize().x/2, interface.getSize().y/2);
        interface.setPosition(window->getSize().x/2, window->getSize().y/2 + buttonSize);
        interfaceTexture.setSmooth(true);
        interface.setTexture(&interfaceTexture);
        interface.setOutlineThickness(4.f);
        interface.setOutlineColor(sf::Color::Black);

        optionsText.setFont(font);
        optionsText.setColor(sf::Color::Black);
        optionsText.setString("Options");
        optionsText.setCharacterSize(1.5*buttonSize);
        optionsText.setOrigin(optionsText.getGlobalBounds().width/2, optionsText.getGlobalBounds().height/2);
        optionsText.setPosition(sf::Vector2f(window->getSize().x/2, window->getSize().y/2 - 2*buttonSize));
        
        musicText.setFont(font);
        musicText.setColor(sf::Color::Black);
        musicText.setString("Music:");
        musicText.setCharacterSize(0.8*buttonSize);
        musicText.setOrigin(musicText.getGlobalBounds().width/2, musicText.getGlobalBounds().height);
        musicText.setPosition(sf::Vector2f(window->getSize().x/2 - 5.5*buttonSize, window->getSize().y/2));

        soundText.setFont(font);
        soundText.setColor(sf::Color::Black);
        soundText.setString("Sound:");
        soundText.setCharacterSize(0.8*buttonSize);
        soundText.setOrigin(musicText.getGlobalBounds().width/2, musicText.getGlobalBounds().height);
        soundText.setPosition(sf::Vector2f(window->getSize().x/2 - 5.5*buttonSize, window->getSize().y/2 + 1.2*buttonSize));
    
        checkSprite.setTexture(checkTexture);

        optionsButtons.push_back(std::make_shared<Button>(
                                    sf::Vector2f(8*buttonSize, buttonSize/4), 
                                    sf::Vector2f(window->getSize().x/2, window->getSize().y/2), 
                                    sf::Color(112, 58, 7) ));
        optionsButtons.push_back(std::make_shared<Button>(
                                    sf::Vector2f(buttonSize, buttonSize), 
                                    sf::Vector2f(window->getSize().x/2 + buttonSize * (data.stats["GameMusic"]["volume"]/12.5 - 4), window->getSize().y/2), 
                                    sf::Color(112, 58, 7)));
        //Music Enabled
        optionsButtons.push_back(std::make_shared<Button>(
                                    sf::Vector2f(buttonSize, buttonSize), 
                                    sf::Vector2f(window->getSize().x/2 + 6 * buttonSize, window->getSize().y/2 - 0.4*buttonSize), 
                                    checkSprite, (static_cast<bool>(dataMap.stats["GameMusic"]["enabled"])) ? sf::Color(204, 107, 16) : sf::Color(112, 58, 7),
                                    (static_cast<bool>(dataMap.stats["GameMusic"]["enabled"])) ));
        //std::cout << dataMap.stats["GameMusic"]["enabled"] << std::endl;
        //Second Slider
        optionsButtons.push_back(std::make_shared<Button>(
                                    sf::Vector2f(8*buttonSize, buttonSize/4), 
                                    sf::Vector2f(window->getSize().x/2, window->getSize().y/2 + 1.2*buttonSize),
                                    sf::Color(112, 58, 7)));
        optionsButtons.push_back(std::make_shared<Button>(
                                    sf::Vector2f(buttonSize, buttonSize), 
                                    sf::Vector2f(window->getSize().x/2 + buttonSize * (data.stats["GameSound"]["volume"]/12.5 - 4), window->getSize().y/2 + 1.2*buttonSize), 
                                    sf::Color(112, 58, 7)));
        //Sound Enabled
        optionsButtons.push_back(std::make_shared<Button>(
                                    sf::Vector2f(buttonSize, buttonSize), 
                                    sf::Vector2f(window->getSize().x/2 + 6 * buttonSize, window->getSize().y/2 + 0.8*buttonSize), 
                                    checkSprite, (static_cast<bool>(dataMap.stats["GameSound"]["enabled"])) ? sf::Color(204, 107, 16) : sf::Color(112, 58, 7),
                                    (static_cast<bool>(dataMap.stats["GameSound"]["enabled"])) ));
        //MenuButton
        optionsButtons.push_back(std::make_shared<Button>(
                                    sf::Vector2f(3*buttonSize, buttonSize), 
                                    sf::Vector2f(window->getSize().x/2, window->getSize().y/2 + 2.6*buttonSize), 
                                    sf::Color(112, 58, 7), sf::Color::Black, "Back", font));
        }
    default:
        break;
    }
}

void GUI::draw(int currentState, std::shared_ptr<sf::RenderWindow> window, int gold)
{
    switch (currentState)
    {
        case MENU_STATE:
        {
            // Draw Buttons in Menu
            for (int i{0} ; i < static_cast<int>(menuButtons.size()) ; i++)
            {
                window->draw(menuButtons.at(i)->draw());
            }
            break;
        }
        case GAME_STATE:
        {
            // Draw Interface and Buttons in Game State
            window->draw(interface);
            window->draw(statsInterface);
            for (int i{0} ; i < static_cast<int>(gameButtons.size()) ; i++)
            {
                coinSprite.setPosition(0.5*buttonSize, 0.5*buttonSize);
                heartSprite.setPosition(0.5*buttonSize, 0.5*buttonSize + coinSprite.getGlobalBounds().height);

                goldText.setString(std::to_string(gold));
                goldText.setPosition(0.5*buttonSize + coinSprite.getGlobalBounds().width, 0.5*buttonSize);

                window->draw(goldText);
                window->draw(coinSprite);
                window->draw(heartSprite);
                window->draw(gameButtons.at(i)->draw());
            }
            break;
        }
        case PAUSE_STATE:
        {
            // Draw Buttons in Pause State
            for (int i{0} ; i < static_cast<int>(pausedButtons.size()) ; i++)
            {
                window->draw(pausedButtons.at(i)->draw());
            }
            break;
        }
        case WIN_STATE:
        {
            // Draw Buttons in Win State
            for (int i{0} ; i < static_cast<int>(winButtons.size()) ; i++)
            {
                window->draw(winButtons.at(i)->draw());
            }
            break;
        }
        case LOSE_STATE:
        {
            // Draw Buttons in Lose State
            for (int i{0} ; i < static_cast<int>(loseButtons.size()) ; i++)
            {
                window->draw(loseButtons.at(i)->draw());
            }
            break;
        }
        // Draw Buttons in Options State

        case OPTIONS_STATE:
        {
            window->draw(interface);
            window->draw(optionsText);
            window->draw(musicText);
            window->draw(soundText);
            for (int i{0} ; i < static_cast<int>(optionsButtons.size()) ; i++)
            {
                window->draw(optionsButtons.at(i)->draw());
            }
            break;
        }
        default:
            break; 
    }
    
}

void GUI::updateLogic(std::shared_ptr<sf::RenderWindow> window, int currentState)
{
    sf::Mouse mouse{}; 

    switch ( currentState )
    {
        case MENU_STATE:
            for (int i{0} ; i < static_cast<int>(menuButtons.size()) ; i++)
            {
                // Call Hover Function when Hovering over Button
                if (menuButtons.at(i)->getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
                {
                    menuButtons.at(i)->hover();
                }
                else
                {
                    menuButtons.at(i)->stopHover(); 
                }
            }
            break;
        case GAME_STATE:
            for (int i{0} ; i < static_cast<int>(gameButtons.size()) ; i++)
            {
                // Call Hover Function when Hovering over Button
                if (gameButtons.at(i)->getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
                {
                    gameButtons.at(i)->hover();
                }
                else
                {
                    gameButtons.at(i)->stopHover(); 
                }
            }
            break;
        case PAUSE_STATE:
            for (int i{0} ; i < static_cast<int>(pausedButtons.size()) ; i++)
            {
                // Call Hover Function when Hovering over Button
                if (pausedButtons.at(i)->getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
                {
                    pausedButtons.at(i)->hover();
                }
                else
                {
                    pausedButtons.at(i)->stopHover(); 
                }
            }
            break;
        case WIN_STATE:
            for (int i{0} ; i < static_cast<int>(winButtons.size()) ; i++)
            {
                // Call Hover Function when Hovering over Button
                if (winButtons.at(i)->getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
                {
                    winButtons.at(i)->hover();
                }
                else
                {
                    winButtons.at(i)->stopHover(); 
                }
            }
            break;
        case LOSE_STATE:
            for (int i{0} ; i < static_cast<int>(loseButtons.size()) ; i++)
            {
                // Call Hover Function when Hovering over Button
                if (loseButtons.at(i)->getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
                {
                    loseButtons.at(i)->hover();
                }
                else
                {
                    loseButtons.at(i)->stopHover(); 
                }
            }
            break;
            case OPTIONS_STATE:
            for (int i{0} ; i < static_cast<int>(optionsButtons.size()) ; i++)
            {
                if ( i == 0 || i == 2 || i == 3 || i == 5 )
                {
                    continue;
                }
                if (optionsButtons.at(i)->getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
                {
                    optionsButtons.at(i)->hover();
                }
                else
                {
                    optionsButtons.at(i)->stopHover(); 
                }
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
            // Return Clicked Button in Menu State
            for (int i{0} ; i < static_cast<int>(menuButtons.size()) ; i++)
                {
                    if (menuButtons.at(i)->getGlobalBounds().contains(mouseX,mouseY))
                    {
                        return i+1;
                    }
                }
            break;
        }
        case GAME_STATE:
        {
            // Return Clicked Button in Game State
            for (int i{0} ; i < static_cast<int>(gameButtons.size()) ; i++)
                {
                    if (gameButtons.at(i)->getGlobalBounds().contains(mouseX,mouseY))
                    {
                        return i+1;
                    }
                }
            break;
        }
        case PAUSE_STATE:
        {
            // Return Clicked Button in Pause State
            for (int i{0} ; i < static_cast<int>(pausedButtons.size()) ; i++)
                {
                    if (pausedButtons.at(i)->getGlobalBounds().contains(mouseX,mouseY))
                    {
                        return i+1;
                    }
                }
            break;
        }
        case WIN_STATE:
        {
            // Return Clicked Button in Win State
            for (int i{0} ; i < static_cast<int>(winButtons.size()) ; i++)
                {
                    if (winButtons.at(i)->getGlobalBounds().contains(mouseX,mouseY))
                    {
                        return i+1;
                    }
                }
            break;
        }
        case LOSE_STATE:
        {
            // Return Clicked Button in Lose State
            for (int i{0} ; i < static_cast<int>(loseButtons.size()) ; i++)
                {
                    if (loseButtons.at(i)->getGlobalBounds().contains(mouseX,mouseY))
                    {
                        return i+1;
                    }
                }
            break;
        }
        case OPTIONS_STATE:
        {
            for (int i{0} ; i < static_cast<int>(optionsButtons.size()) ; i++)
            {
                if (optionsButtons.at(i)->getGlobalBounds().contains(mouseX,mouseY))
                {
                    if ( i == 2 )
                    {
                        optionsButtons.at(i)->click();
                    }
                    else if ( i == 5 )
                    {
                        optionsButtons.at(i)->click();
                    }
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
unsigned int GUI::sliderPosition(int buttonNmbr, float mouseX)
// Function to return where the slider is currently being dragged
{
    optionsButtons.at(buttonNmbr)->setPosition(mouseX);

    if ( optionsButtons.at(buttonNmbr)->getPosition().x <= 
         optionsButtons.at(0)->getGlobalBounds().left )
    {
        optionsButtons.at(buttonNmbr)->setPosition(optionsButtons.at(0)->getGlobalBounds().left);
    }
    else if ( optionsButtons.at(buttonNmbr)->getPosition().x >= 
              optionsButtons.at(0)->getGlobalBounds().left + optionsButtons.at(0)->getGlobalBounds().width )
    {
        optionsButtons.at(buttonNmbr)->setPosition(optionsButtons.at(0)->getGlobalBounds().left + optionsButtons.at(0)->getGlobalBounds().width);
    }
    else
    {
    }
    return std::round(100 * ( optionsButtons.at(buttonNmbr)->getPosition().x - optionsButtons.at(0)->getGlobalBounds().left ) / 
                            ( optionsButtons.at(0)->getGlobalBounds().width ));
}

void GUI::drawHPBar(std::shared_ptr<sf::RenderWindow> window, const sf::Sprite& groundSprite, int friendlyHP, int enemyHP)
{
    enemyHealthBar.setPosition(19*window->getSize().x/20 - buttonSize/2*1.5, 8*buttonSize);
    enemyHealthBar.setScale(1/1.5, 1/1.5);
    enemyHealthRec.setPosition(enemyHealthBar.getPosition().x, enemyHealthBar.getPosition().y);
    enemyHealthRec.setScale(sf::Vector2f(1/1.5, static_cast<double>(enemyHP)/static_cast<double>(originalBaseHP)/1.5));
    
    // Set Current Health Bar
    healthBar.setPosition(buttonSize/2*1.5, 8*buttonSize);
    healthBar.setScale(1/1.5, 1/1.5);
    healthRec.setPosition(healthBar.getPosition().x, healthBar.getPosition().y);
    healthRec.setScale(sf::Vector2f(1/1.5, static_cast<double>(friendlyHP)/static_cast<double>(originalBaseHP)/1.5));
    
    // Draw Health Bars
    window->draw(enemyHealthBar);
    window->draw(enemyHealthRec);
    window->draw(healthBar);
    window->draw(healthRec);
}