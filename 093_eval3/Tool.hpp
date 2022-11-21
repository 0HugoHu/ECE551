#ifndef TOOL_HPP
#define TOOL_HPP

#include "Page.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>

#define NORMAL 9000
#define WIN 9001
#define LOSE 9002
#define CHOICE 9005
#define INVALID 9009

// ReadLine Class provides input and output abstact functions
class ReadLine
{
private:
    std::size_t index;
    std::size_t choice;
    std::string pageName;
    std::string choiceContent;

public:
    ReadLine() : index(0), choice(0) {}
    void initPage(std::string inputFile, std::vector<Page *> &pages);
    std::vector<std::string> readLine(std::string filename);
    void printLine(std::string filename);
    int parseLineType(std::string line);
    std::size_t getIndex();
    std::size_t getChoice();
    std::string getPageName();
    std::string getChoiceContent();
    ~ReadLine() {}
};

#endif
