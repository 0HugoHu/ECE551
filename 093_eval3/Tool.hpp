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
#define VARIABLE 9006
#define CONDITION 9007
#define INVALID 9009

#define RANDOM_NUM1 92295225
#define RANDOM_NUM2 24118035

#define EXIT_SUCCESS 0

// ReadLine Class provides input and output abstact functions
class ReadLine
{
private:
    std::size_t index;
    std::size_t choice;
    std::string pageName;
    std::string choiceContent;
    std::pair<size_t, std::string> pageStartVar;
    std::pair<std::string, long int> pageStartVarValue;
    std::pair<std::string, long int> choiceCondition;
    bool isStep4;

public:
    ReadLine() : index(0), choice(0), isStep4(false) {}
    void initPage(std::string inputFile, std::vector<Page *> &pages);
    std::vector<std::string> readLine(std::string filename);
    void printLine(std::string filename);
    int parseLineType(std::string line);
    std::size_t getIndex();
    std::size_t getChoice();
    std::string getPageName();
    std::string getChoiceContent();
    std::pair<size_t, std::string> getPageStartVar();
    std::pair<std::string, long int> getPageStartVarValue();
    std::pair<std::string, long int> getChoiceCondition();
    void setIsStep4(bool b);
    ~ReadLine() {}
};

class CheckPages
{
private:
    std::vector<std::size_t> pages;
    std::vector<std::vector<std::size_t> > choices;
    bool checkedWinAndLose;
    bool checkWin(std::string &type);
    bool checkLose(std::string &type);

public:
    CheckPages(std::vector<Page *> &pages);
    bool checkPages();
    bool checkChoices();
    bool getWinAndLoseStatus();
};

#endif
