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
    PauseState   (std::shared_ptr<sf::RenderWindow>, sf::Music*, sf::Time*);
    ~PauseState  () override;
    PauseState   (const PauseState&) = delete;
    PauseState& operator= ( const PauseState& ) = delete;

private:
    // FUNCTIONS
    void    handleEvent     (sf::Event)                         override;
    void    renderFrame     ()                                  override;
    int     getNextState    ()                                  override;
    void    updateLogic     ()    override;
    void    startAnimation  ();
    void    resetState()     override;

    // VARIABLES
    int nextstate;
    std::string fontFile;

    sf::Font*           textFont;
    sf::Text*           pausedText;
    sf::RectangleShape* greyOut;
};

#endif