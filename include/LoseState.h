#ifndef LOSESTATE_H
#define LOSESTATE_H

#include "State.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

class LoseState: public State
{
    public:
    // CONSTRUCTORS / DESTRUCTORS
    LoseState(std::shared_ptr<sf::RenderWindow>, FileReader::Data&, std::shared_ptr<sf::Music>, std::shared_ptr<sf::Time>);
    ~LoseState() override;
    LoseState(const LoseState&) = delete;
    LoseState& operator= (const LoseState&) = delete;

    // FUNCTIONS
    void handleEvent (sf::Event) override;
    void updateLogic ()          override;
    void renderFrame ()          override;
    int getNextState ()          override;
    void resetState ()           override;

    private:
    int nextState;

    sf::Font*           textFont;
    sf::Text*           loseText;
    sf::RectangleShape* greyOut;
};

#endif