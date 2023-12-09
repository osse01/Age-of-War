#include "../include/State.h"

State::State(std::shared_ptr<sf::RenderWindow> window, FileReader::Data& dataMap, std::shared_ptr<sf::Music> music, std::shared_ptr<sf::Time> frameDuration)
: window { window }, music { music }, frameDuration { frameDuration }, dataMap{dataMap}
{}

State::~State()
{}
void State::prevState(int __attribute__((unused)))
{
    return;
}