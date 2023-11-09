#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"

#include <string>



class MenuState : public State
//  =============   MenuState CLASS    ===============
//  This Class Handles ...
{
public:
    // CONSTRUCTORS
    MenuState   (sf::RenderWindow*, int&);
    ~MenuState  () = default;

private:
    // FUNCTIONS
    void    handleEvent     (sf::Event)                         override;
    void    renderFrame     (sf::RenderWindow&)                 override;
    int     getNextState    ()                                  override;
    void    updateLogic     (sf::Time const & frameDuration)    override;
    void    startAnimation  ();

    // VARIABLES
    float   scale;
    float   t;

    std::string     fontFile;
    std::string     backroundFile;

    sf::Image*          image;
    sf::Texture*        texture;
    sf::Sprite*         sprite;
    sf::Font*           textFont;
    sf::Text*           gameTitle;
    sf::Text*           instructionText;
    sf::RenderWindow*   window;
};

#endif