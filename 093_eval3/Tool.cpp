#include "Tool.hpp"

int ReadLine::parseLineType(std::string line)
{
    std::size_t index = 0;
    int type = 0;

    // Page Type
    // 0@N:page0.txt
    std::size_t foundAt = line.find("@");
    // Index
    if (foundAt != std::string::npos)
    {
        std::string segmentIndex = line.substr(0, foundAt);
        char *endptr;
        index = strtoul(segmentIndex.c_str(), &endptr, 10);
        if (endptr == segmentIndex.c_str() || *endptr != '\0' || index < 0)
        {
            return INVALID;
        }
        this->index = index;
        
        
        // Type
        std::size_t foundCol = line.find(":");
        if (foundCol != std::string::npos)
        {
            std::string segmentType = line.substr(foundAt + 1, foundCol - foundAt - 1);
            if (segmentType == "N")
            {
                type = NORMAL;
            }
            else if (segmentType == "W")
            {
                type = WIN;
            }
            else if (segmentType == "L")
            {
                type = LOSE;
            }
            else
            {
                return INVALID;
            }

            // File Name
            std::string segmentFileName = line.substr(foundCol + 1);
            std::size_t foundFile = segmentFileName.find(".txt");
            // Not contain ".txt"
            if (foundFile == std::string::npos || foundFile - foundCol == 0)
            {
                return INVALID;
            }
            this->pageName = segmentFileName;
            return type;
        }
        else
        {
            return INVALID;
        }
    }

    // Choice Type
    // 2:1:Something
    std::size_t foundCol = line.find(":");
    // index
    if (foundCol != std::string::npos)
    {
        std::string segmentIndex = line.substr(0, foundCol);
        char *endptr;
        index = strtoul(segmentIndex.c_str(), &endptr, 10);
        if (endptr == segmentIndex.c_str() || *endptr != '\0' || index < 0)
        {
            return INVALID;
        }
        this->index = index;

        std::string lineAfter = line.substr(foundCol + 1);
        std::size_t foundSecondCol = lineAfter.find(":");
        // choice (goto)
        if (foundSecondCol != std::string::npos)
        {
            std::string segmentChoice = lineAfter.substr(0, foundSecondCol);
            
            char *endptr2;
            index = strtoul(segmentChoice.c_str(), &endptr2, 10);
            if (endptr2 == segmentChoice.c_str() || *endptr2 != '\0' || index < 0)
            {
                return INVALID;
            }
            this->choice = index;

            // Choice Content
            std::string segmentChoiceContent = lineAfter.substr(foundSecondCol + 1);
            if (segmentChoiceContent.size() == 0)
            {
                return INVALID;
            }
            this->choiceContent = segmentChoiceContent;
            return CHOICE;
        }
        else
        {
            return INVALID;
        }
    }
    else
    {
        return INVALID;
    }

    return INVALID;
}

std::vector<std::string> ReadLine::readLine(std::string filename)
{
    std::ifstream f;
    f.open(filename.c_str());
    if (!f.is_open())
    {
        std::cerr << "Cannot open the file!" << std::endl;
    }
    std::vector<std::string> res;
    std::string line;
    while (getline(f, line))
    {
        if (line != "\n" && line.size() >= 4)
        {
            res.push_back(line);
        }
    }
    f.close();

    return res;
}

void ReadLine::printLine(std::string filename)
{
    std::ifstream f;
    f.open(filename.c_str());
    if (!f.is_open())
    {
        std::cerr << "Cannot open the file!" << std::endl;
    }
    std::string line;
    while (getline(f, line))
    {
        std::cout << line << std::endl;
    }
    f.close();
}

std::size_t ReadLine::getIndex()
{
    return this->index;
}

std::size_t ReadLine::getChoice()
{
    return this->choice;
}

std::string ReadLine::getPageName()
{
    return this->pageName;
}

std::string ReadLine::getChoiceContent()
{
    return this->choiceContent;
}
