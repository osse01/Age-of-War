#ifndef GAME_H
#define GAME_H

#include "State.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <memory>



class Game
//  =============   Game CLASS    ===============
{
    public:
    //  CONSTRUCTORS / DESTRUCTORS //
    Game( std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight );
    virtual ~Game() = default;

    //  FUNCTIONS //
    void startGame    ();
    void handleEvents ();
    void updateLogic  (sf::Time const &);
    void renderFrame  ();
    void getNextState ();
    

    private:
    // Variables //
    sf::RenderWindow* window; // Possibly Use RenderWindow* Instead
    sf::Event event;
    bool running;
    
    // States
    std::vector<State*> gameStates;
    int     currentState;
    int*    currentStatePtr;

    protected:
        int    nextState;




};

#endif
