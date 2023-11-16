#include "../include/State.h"

State::State(sf::Music* music, sf::Time* frameDuration)
:music { music }, frameDuration { frameDuration }
{}

State::~State()
{
    music = nullptr;
    frameDuration = nullptr;
}
