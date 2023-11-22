#include "../include/Base.h"

Base::Base(const FileReader::Data& stats,  bool friendly, sf::Vector2f pos)
    : Entity::Entity(stats, friendly, pos), base {  }
{
    // if(!texture.loadFromFile(stats.filename))
    // {
    //     throw std::logic_error(
    //     "    >> Error: Could Not Find background image. Error in Base::Base().");
    // }
    
    


} 