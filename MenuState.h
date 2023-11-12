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
    MenuState   (sf::RenderWindow*, int*, sf::Music*);
    ~MenuState  () = default;

    private:
    // FUNCTIONS
    void    handleEvent     (sf::Event)                         override;
    void    renderFrame     ()                                  override;
    int     getNextState    ()                                  override;
    void    updateLogic     (sf::Time const & frameDuration)    override;
    void    startAnimation  ();

    // VARIABLES
    float   scale;
    float   t;
    int*    currentState;
    sf::Music* music;

    std::string     fontFile;
    std::string     backgroundFile;

    sf::Image*          image;
    sf::Texture*        texture;
    sf::Sprite*         sprite;
    sf::Font*           textFont;
    sf::Text*           gameTitle;
    sf::Text*           instructionText;
    sf::RenderWindow*   window;
    sf::Vector2f        zoomFactor;
    };

    #endif