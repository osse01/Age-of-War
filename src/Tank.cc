#include "../include/Tank.h"

Tank::Tank(FileReader::Data& data, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
 : Troop::Troop(data, "Tank", friendly, pos, frameDuration)
{}