#include "Tool.hpp"

int Tool::parseLineType(std::string &line)
{
    std::stringstream sstream(line);
    std::string segment;
    size_t index = 0;
    int type = 0;
    int i = 0;
    while (getline(sstream, segment, '@'))
    {
        if (i == 0)
        {
            char *endptr;
            index = strtoul(segment, &endptr, 10);
            if (endptr == str || *endptr != '\0' || index < 0)
            {
                return INVALID;
            }
        }
        else
        {
            while (getline(sstream, segment, ':'))
            {
                if (i == 1) {
                    if (segment == "N") type = NORMAL;
                    else if (segment == "W") type = WIN;
                    else if (segment == "L") type = LOSE;
                    else return INVALID;
                } else {

                }
            }
        }
        i++;
    }
    if (type == 0) return CHOICE;

}

int Tool::getIndex()
{
    return index;
}

std::string Tool::getPageName()
{
    return pageName;
}