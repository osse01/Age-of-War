#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "FileReader.h"

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
    //  FUNCTIONS //
    void saveFrame();

    // Variables //
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Time> frameDurationPtr;

    sf::Event event;
    sf::Clock clock;
    
    // States //
    std::stack<std::unique_ptr<State>> states;
    sf::Texture lastFrame;
    int     currentState;
    int     nextState;

    // Sounds //
    std::vector<std::shared_ptr<sf::SoundBuffer>> soundBuffer;
    std::map<std::string, std::shared_ptr<sf::Sound>> sound;
    std::shared_ptr<sf::Music> music;

    //--------//

    sf::Sprite cursorSprite;
    sf::Texture cursor;

    sf::Mouse mouse;

    FileReader::Data dataMap;
};

#endif
