#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

class FileReader
//  -------------------------------------------------------
//  FileReader class contains functions for reading data
//  from .txt files and can return that data in vector
//  format for easy acces to the data.
//
//  Data will be acceseble through vector with string 
//  elements, format for current project in the srings are
//  TYPE-/-DAMAGE-/-HP-/-MOVEMENTSPEED-/-RANGE-/-ATTACKSPEED-/-BOX_SIZE-/-TEXTUREFILE
//  -------------------------------------------------------

{
public:
//  CONSTRUCTORS
    FileReader  (const std::string&, const std::string&);
    ~FileReader ()              = default;
    FileReader  (FileReader&)   = delete;
    FileReader  (FileReader&&)  = delete; 

//  OPERATORS
    FileReader& operator = (const FileReader&)  = delete;
    FileReader& operator = (FileReader&&)       = delete;

//  STRUCTURES
    struct Data
    {
        int damage;
        int hp;
        int attackSpeed;
        int movementSpeed;
        int boxSize;

        std::string type;
        std::string filename;
    };

//  FUNCTIONS
    Data    getData();

private:
//  FUNCTIONS
    bool    readFile();
    Data    returnData(const std::string&);

//  VARIABLES
    std::string     filename;
    std::string     objectName;

    Data    data;
    
    std::vector<std::string> fileContents;
};

#endif