#include "../include/State.h"

State::State(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Music> music, std::shared_ptr<sf::Time> frameDuration)
: window { window }, music { music }, frameDuration { frameDuration }
{}

State::~State()
{}
