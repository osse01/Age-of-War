#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "State.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


class CreditsState: public State
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    CreditsState( std::shared_ptr<sf::RenderWindow>, 
                  FileReader::Data&, std::shared_ptr<sf::Music>, 
                  std::map<std::string, std::shared_ptr<sf::Sound>>, 
                  std::shared_ptr<sf::Time>);
    ~CreditsState() override;
    CreditsState( const CreditsState& ) = delete;
    CreditsState& operator= ( const CreditsState& ) = delete;  

private:
    // FUNCTIONS
    void    handleEvent    ( sf::Event ) override;
    void    updateLogic    ()            override;
    void    renderFrame    ()            override;
    int     getNextState   ()            override;
    void    resetState     ()            override;
    void    setupCanvas    ();
    
    // VARIABLES
    std::vector<sf::Text>   nameList;
    sf::RenderTexture       canvas;
    sf::Texture             backgroundTexture;
    sf::Texture             fadeTexture;
    sf::Sprite              backgroundSprite1;
    sf::Sprite              backgroundSprite2;
    sf::Sprite              canvasSprite;
    sf::Sprite              fadeSprite;
    sf::Font                nameFont;
    sf::Font                textFont;

    double                  elapsedTime;
    int                     nextState;

};

#endif