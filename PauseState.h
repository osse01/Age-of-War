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
    PauseState   (sf::RenderWindow*, int*);
    ~PauseState  () = default;

private:
    // FUNCTIONS
    void    handleEvent     (sf::Event)                         override;
    void    renderFrame     ()                                  override;
    int     getNextState    ()                                  override;
    void    updateLogic     (sf::Time const & frameDuration)    override;
    void    startAnimation  ();

    // VARIABLES
    int*    currentState;

    std::string fontFile;

    sf::RenderWindow*   window;
    sf::Font*           textFont;
    sf::Text*           pausedText;
    sf::RectangleShape* greyOut;
};

#endif