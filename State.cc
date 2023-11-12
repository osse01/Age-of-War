#include "State.h"
#include <iostream>

State::~State()
{
    currentState = nullptr;
    music = nullptr;
    std::cout << "Hej" << std::endl;
}