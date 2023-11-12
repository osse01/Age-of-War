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
    MenuState   (sf::RenderWindow*, int*, sf::Music*, sf::Time*);
    ~MenuState  () override;
    MenuState   (const MenuState&) = delete;
    MenuState& operator= ( const MenuState& ) = delete;

    private:
    // FUNCTIONS
    void    handleEvent     (sf::Event)                         override;
    void    renderFrame     ()                                  override;
    int     getNextState    ()                                  override;
    void    updateLogic     ()          override;
    void    startAnimation  ();

    // VARIABLES
    float   scale;
    float   t;
    int*    currentState;

    std::string     fontFile;
    std::string     backgroundFile;

    sf::Texture        texture;
    sf::Sprite         sprite;
    sf::Font           textFont;
    sf::Text           gameTitle;
    sf::Text           instructionText;
    sf::RenderWindow*   window;
    sf::Vector2f        zoomFactor;
    };

    #endif