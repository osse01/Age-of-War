#ifndef GAME_H
#define GAME_H

#include "State.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <iostream>
#include <memory>
#include <stack>



class Game
//  =============   Game CLASS    ===============
{
    public:
    //  CONSTRUCTORS / DESTRUCTORS //
    Game( std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight );
    ~Game();
    Game(const Game&) = delete;
    Game& operator= (const Game&) = delete;


    //  FUNCTIONS //
    void startGame    ();
    void handleEvents ();
    void updateLogic  ();
    void renderFrame  ();
    void getNextState ();
    

    private:
    // Variables //
    sf::RenderWindow* window; // Possibly Use RenderWindow* Instead
    sf::Event event;
    bool running;
    sf::Clock clock;
    sf::Time frameDuration;
    sf::Time* frameDurationPtr;
    
    // States
    std::stack<std::unique_ptr<State>> states;
    int     currentState;
    //int*    currentStatePtr;
    sf::Music* music;
    

    protected:
    int    nextState;




};

#endif
