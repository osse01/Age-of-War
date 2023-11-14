#ifndef PauseState_H
#define PauseState_H

#include "State.h"

#include <string>



class PauseState : public State
//  =============   PauseState CLASS    ===============
//  This Class Handles ...
{
public:
    // CONSTRUCTORS
    PauseState   (sf::RenderWindow*, int*, sf::Music*, sf::Time*);
    ~PauseState  () override;
    PauseState   (const PauseState&) = delete;
    PauseState& operator= ( const PauseState& ) = delete;

private:
    // FUNCTIONS
    void    handleEvent     (sf::Event)                         override;
    bool    renderFrame     ()                                  override;
    int     getNextState    ()                                  override;
    void    updateLogic     ()    override;
    void    startAnimation  ();

    // VARIABLES
    int*    currentState;
    int     nextState;

    std::string fontFile;

    sf::RenderWindow*   window;
    sf::Font*           textFont;
    sf::Text*           pausedText;
    sf::RectangleShape* greyOut;
};

#endif