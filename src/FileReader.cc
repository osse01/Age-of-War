#include "../include/FileReader.h"

FileReader::FileReader(std::shared_ptr<sf::RenderWindow> window)
:
    // Data Member Initialization List
    //---------------------------------------
    windowScale { window->getSize().x/1920.f }, 
    data        {}
    //---------------------------------------
{}

FileReader::Data FileReader::returnData(const std::string& filename)
//  -------------------------------------------------------
//  Returns Data Struct Containing all Information from the String
//  Starting with Argument Name
//  -------------------------------------------------------
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        throw std::logic_error("\n  >> Error: Failed to open the file <" 
        + filename +  "> in FileReader::returnData()");
    }
    else
    {
        Data data{};
        std::string lastKey {};
        while (std::getline(file, line))
        {
            std::istringstream dataline {line};
            std::string tmp {};

            dataline >> tmp;

            if (tmp.empty())
            {
                continue;
            }
            if (dataline.str() == tmp)
            {
                data.stats[tmp];
                data.files[tmp];
                lastKey = tmp;
            }
            else if (tmp == "filename")
            {
                dataline >> data.files[lastKey];
            }
            else if (tmp == "spriteDim")
            {
                dataline >> data.spriteDim[lastKey].x >> data.spriteDim[lastKey].y;
            }
            else if (tmp == "boxSize")
            {
                dataline >> data.boxSize[lastKey].x >> data.boxSize[lastKey].y;
            }
            else
            {
                dataline >> data.stats[lastKey][tmp];
            }
        }
        file.close();

        data.windowScale = windowScale;

        return data;
    }
}