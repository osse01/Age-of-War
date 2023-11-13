#include "FileReader.h"


FileReader::FileReader(const std::string& file, const std::string& type)
:   filename{file}, objectName{type}, data{}, fileContents{}
//  -------------------------------------------------------
{
    readFile();
    data = returnData(objectName);
}

bool FileReader::readFile()
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
        return false;
    }

    else
    {
        while (std::getline(file, line)) {
            fileContents.push_back(line);
        }
        file.close();
        return true;
    }
}

FileReader::Data FileReader::returnData(const std::string& name)
//  -------------------------------------------------------
//  Returns Data Struct Containing all Info from the String
//  Starting with Argument Name. 
//  -------------------------------------------------------
{
    Data data{};
    std::string tmp{};

    for (const auto& element : fileContents)
    {
        std::istringstream dataline{element};
        dataline >> tmp;

        if (tmp == name)
        {
            dataline >> data.damage >> data.hp >> data.movementSpeed
                      >> data.attackSpeed >> data.boxSize >> data.filename;
            break;
        }
    }

    return data;
}

FileReader::Data FileReader::getData()
//  -------------------------------------------------------
//  Getter for data Variable.
//  -------------------------------------------------------
{
    return data;
}
