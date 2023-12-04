#ifndef PauseState_H
#define PauseState_H

#include "State.h"

#include <string>
#include <memory>




class PauseState : public State
//  =============   PauseState CLASS    ===============
//  This Class Handles ...
{
public:
    // CONSTRUCTORS
    PauseState   (std::shared_ptr<sf::RenderWindow>, FileReader::Data&, std::shared_ptr<sf::Music>, std::shared_ptr<sf::Time>);
    ~PauseState  () override;
    PauseState   (const PauseState&) = delete;
    PauseState& operator= ( const PauseState& ) = delete;

private:
    // FUNCTIONS
    void    handleEvent     (sf::Event) override;
    void    renderFrame     ()          override;
    int     getNextState    ()          override;
    void    updateLogic     ()          override;
    void    resetState      ()          override;
    
    // VARIABLES
    int nextstate;

    sf::Font            textFont;
    sf::Text            pausedText;
    sf::RectangleShape  greyOut;
};

#endif