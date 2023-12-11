#include "../include/State.h"

State::State(std::shared_ptr<sf::RenderWindow> window, FileReader::Data& dataMap, std::shared_ptr<sf::Music> music, std::map<std::string, std::shared_ptr<sf::Music>> sound, std::shared_ptr<sf::Time> frameDuration)
: window { window }, music { music }, sound {sound}, frameDuration { frameDuration }, dataMap{dataMap}
{}

State::~State()
{}
void State::prevState(int __attribute__((unused)))
{
    return;
}