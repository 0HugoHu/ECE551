#ifndef TOOL_HPP
#define TOOL_HPP

#include <vector>
#include <string>
#include <sstream>

#define NORMAL 9000
#define WIN 9001
#define LOSE 9002
#define CHOICE 9005
#define INVALID 9009

class Tool
{
private:
    int index;
    std::string pageName;

public:
    int parseLineType(std::string line);
    int getIndex();
    std::string getPageName();
};

#endif