#include "../include/FileReader.h"


FileReader::FileReader(std::shared_ptr<sf::RenderWindow> window)
    : windowScale {window->getSize().x/1920.f}, data{}, enemy{}, fileContents{}
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

    for (const auto& element : fileContents)
    {
        std::istringstream dataline{element};
        dataline >> tmp;

        if (tmp == name)
        {
            data.type = name;
            
            dataline >> data.damage >> data.hp >> data.movementSpeed >> data.range
                      >> data.attackSpeed >> data.boxSize.x >> data.boxSize.y 
                      >> data.cost  >> data.deathValue
                      >> data.spriteDim.x >> data.spriteDim.y >> data.filename;

            data.movementSpeed *= windowScale;
            data.range *= windowScale;
            data.boxSize.x *= windowScale;
            data.boxSize.y *= windowScale;
            break;
        }

    }

    data.windowScale = windowScale;

    return data;
}

FileReader::Enemy FileReader::getEnemyData(const std::string& name, const std::string& filename)
//  -------------------------------------------------------
//  Returns Data Struct Containing all Info from the String
//  Starting with Argument Name. 
//  -------------------------------------------------------
{
    readFile(filename);
    Enemy enemy{};
    std::string tmp{};

    for (const auto& element : fileContents)
    {
        std::istringstream dataline{element};
        dataline >> tmp;

        if (tmp == name)
        {
            enemy.type = name;
            
            dataline >> enemy.waveSize >> enemy.spawnListSize >> enemy.spawnCount >> enemy.delayCount;
            break;
        }

    }

    data.windowScale = windowScale;

    return enemy;
}