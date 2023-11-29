#ifndef FILEREADER_H
#define FILEREADER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <memory>

class FileReader
//  -------------------------------------------------------
//  FileReader class contains functions for reading data
//  from .txt files and can return that data in vector
//  format for easy acces to the data.
//
//  Data will be acceseble through struct called Data.
//  FileReader funtion returnData(const std::string) Assumes
//  the Data Read From StageX.txt File is in Format:
//  TYPE-/-DAMAGE-/-HP-/-MOVEMENTSPEED-/-RANGE-/-ATTACKSPEED
//  -/-BOX_SIZE-/-COST-/-DEATH_VALUE-/-SPRITE_DIM-/-TEXTUREFILE
//
//  Intended Use, to Create a FileReader Object Giving 
//  it the Correct File Path To Stage Data File and Also
//  Wich Type of Object we are Supposed To fetch Data for.
//  Then Call getData() to get a Struct Containing the 
//  Desired Data.
//  -------------------------------------------------------

{
public:
//  CONSTRUCTORS
    FileReader  (std::shared_ptr<sf::RenderWindow>);
    ~FileReader ()              = default;
    FileReader  (FileReader&)   = delete;
    FileReader  (FileReader&&)  = delete; 

//  OPERATORS
    FileReader& operator = (const FileReader&)  = delete;
    FileReader& operator = (FileReader&&)       = delete;

//  STRUCTURES
    struct Data
    {
        int     damage;
        int     hp;
        float   movementSpeed;
        float   range;
        int     attackSpeed;
        sf::Vector2f boxSize;
        int     cost;
        int     deathValue;

        sf::Vector2i spriteDim;

        std::string type;
        std::string filename;

        float windowScale;
    };

    struct Enemy
    {
        int waveSize;
        int spawnListSize;
        int spawnCount;
        int delayCount;

        std::string type;
    };

//  FUNCTIONS
    Data    returnData(const std::string&, const std::string&);

    Enemy   getEnemyData(const std::string&, const std::string&);

private:
//  FUNCTIONS
    void    readFile(const std::string&);

//  VARIABLES

    float windowScale;
    
    Data    data;
    Enemy   enemy;
    
    std::vector<std::string> fileContents;
};

#endif