#include "../include/FileReader.h"
#include <iostream>

FileReader::FileReader(std::shared_ptr<sf::RenderWindow> window)
    : data{}, windowScale {window->getSize().x/1920.f}
//  -------------------------------------------------------
{}

FileReader::Data FileReader::returnData(const std::string& filename)
//  -------------------------------------------------------
//  Returns Data Struct Containing all Info from the String
//  Starting with Argument Name. 
//  -------------------------------------------------------
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        throw std::logic_error("\n  >> Error: Failed to open the file <" 
        + filename +  "> in FileReader::readFile()");
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
                data.dimensions[tmp];
                lastKey = tmp;
            }
            else if (tmp == "filename")
            {
                dataline >> data.files[lastKey];
            }
            else if (tmp == "boxSize" || tmp == "spriteDim")
            {
                dataline >> data.dimensions[lastKey][tmp].x >> data.dimensions[lastKey][tmp].y;
            }
            else
            {
                dataline >> data.stats[lastKey][tmp];
            }
        }
        file.close();

        data.windowScale = {windowScale};

        return data;

    }

}
