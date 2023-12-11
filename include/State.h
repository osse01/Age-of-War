#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>

#include "FileReader.h"



int const MENU_STATE    { 0 };
int const GAME_STATE    { 1 };
int const PAUSE_STATE   { 2 };
int const WIN_STATE     { 3 };
int const LOSE_STATE    { 4 };
int const CREDITS_STATE { 5 }; 
int const OPTIONS_STATE { 6 };

class State
//  =============   State CLASS    ===============
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    State(std::shared_ptr<sf::RenderWindow>, FileReader::Data&, std::shared_ptr<sf::Music>, 
          std::map<std::string, std::shared_ptr<sf::Music>>, std::shared_ptr<sf::Time>);
    virtual ~State();
    State(const State&) = delete;
    State& operator= (const State&) = delete;

    // FUNCTIONS
    virtual void handleEvent  (sf::Event) = 0;
    virtual void updateLogic  ()          = 0;
    virtual void renderFrame  ()          = 0;
    virtual int  getNextState ()          = 0;
    virtual void resetState   ()          = 0;
    virtual void prevState    (int);

protected:
    std::shared_ptr<sf::RenderWindow>   window;
    std::shared_ptr<sf::Music> music;
    std::map<std::string, std::shared_ptr<sf::Music>> sound;
    std::shared_ptr<sf::Time> frameDuration;
    FileReader::Data& dataMap;
};

#endif