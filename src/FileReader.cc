#include "../include/FileReader.h"


FileReader::FileReader()
    : data{}, fileContents{}
//  -------------------------------------------------------
{}

void FileReader::readFile(const std::string& filename)
//  -------------------------------------------------------
//  Reads .txt Contents Into Strings and Adds them to 
//  fileContents Vector and returns true if successful.
//  -------------------------------------------------------
{
    std::ifstream file(filename);
    std::string line;
    fileContents.clear();

    if (!file.is_open()) {
        throw std::logic_error("\n  >> Error: Failed to open the file <" 
        + filename +  "> in FileReader::readFile()");
    }

    else
    {
        while (std::getline(file, line)) {
            fileContents.push_back(line);
        }
        file.close();
    }
}

FileReader::Data FileReader::returnData(const std::string& name, const std::string& filename)
//  -------------------------------------------------------
//  Returns Data Struct Containing all Info from the String
//  Starting with Argument Name. 
//  -------------------------------------------------------
{
    readFile(filename);
    Data data{};
    std::string tmp{};
    int spriteX{};
    int spriteY{};

    for (const auto& element : fileContents)
    {
        std::istringstream dataline{element};
        dataline >> tmp;

        if (tmp == name)
        {
            data.type = name;
            dataline >> data.damage >> data.hp >> data.movementSpeed >> data.range
                      >> data.attackSpeed >> data.boxSize >> data.cost  >> data.deathValue
                      >> spriteX >> spriteY >> data.filename;
            break;
        }
    }
    (data.spriteDim).x = spriteX;
    (data.spriteDim).y = spriteY;

    return data;
}
