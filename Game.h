#ifndef GAME_H
#define GAME_H

#include "State.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <iostream>
#include <memory>



class Game
//  =============   Game CLASS    ===============
{
    public:
    //  CONSTRUCTORS / DESTRUCTORS //
    Game( std::string const & GAME_TITLE, unsigned gameWidth, unsigned gameHeight );
    ~Game();
    Game(const Game&) = delete;
    Game operator= (const Game&) = delete;


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
    std::vector<State*> states;
    int     currentState;
    int*    currentStatePtr;
    sf::Music* music;

    protected:
        int    nextState;




};

#endif
