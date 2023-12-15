#ifndef FILEREADER_H
#define FILEREADER_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <map>

class FileReader
//  -------------------------------------------------------
//  FileReader class contains functions for reading data
//  from .txt files and can return that data in vector
//  format for easy acces to the data.
//  -------------------------------------------------------
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    FileReader  ( std::shared_ptr<sf::RenderWindow> );
    ~FileReader()              = default;
    FileReader( FileReader&  ) = delete;
    FileReader( FileReader&& ) = delete; 

    // OPERATORS
    FileReader& operator= ( const FileReader& ) = delete;
    FileReader& operator= ( FileReader&& )      = delete;

    // STRUCTURES
    struct Data
    {
        std::map<std::string, 
        std::map<std::string, float>>       stats;

        std::map<std::string, sf::Vector2i> spriteDim;
        std::map<std::string, sf::Vector2f> boxSize;
        std::map<std::string, std::string>  files;

        float                               windowScale;
    };

    // FUNCTIONS
    Data    returnData( const std::string& );

private:
    //  VARIABLES
    float   windowScale; 
    Data    data;
};

#endif