    #ifndef MENUSTATE_H
    #define MENUSTATE_H

    #include "State.h"
    #include "GUI.h"

    #include <string>
    #include <memory>




    class MenuState : public State
    //  =============   MenuState CLASS    ===============
    //  This Class Handles the Main Menu.
    {
    public:
    // CONSTRUCTORS
    MenuState   (std::shared_ptr<sf::RenderWindow>, FileReader::Data&, std::shared_ptr<sf::Music>, 
                 std::map<std::string, std::shared_ptr<sf::Sound>>, std::shared_ptr<sf::Time>);
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
    void    resetState()        override;

    // VARIABLES
    float   scale;
    float   t;
    int     nextState;

    sf::Texture        texture;
    sf::Sprite         sprite;
    sf::Font           textFont;
    sf::Text           gameTitle;
    sf::Text           instructionText;
    sf::Vector2f       zoomFactor;
    GUI                gui;
    
    };

    #endif