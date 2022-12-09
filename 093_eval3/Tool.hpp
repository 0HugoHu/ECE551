#ifndef TOOL_HPP
#define TOOL_HPP

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Page.hpp"

// Define values for line parse
#define NORMAL 9000
#define WIN 9001
#define LOSE 9002
#define CHOICE 9005
#define VARIABLE 9006
#define CONDITION 9007
#define INVALID 9009

// Random number for setting the end of vector with fixed length
#define RANDOM_NUM1 92295225
#define RANDOM_NUM2 24118035

#define EXIT_SUCCESS 0

// ReadLine Class provides input and output abstact functions
class ReadLine {
 private:
  std::size_t index;                            // Current line index
  std::size_t choice;                           // Choice number
  std::string pageName;                         // Page file name
  std::string choiceContent;                    // Content of choice
  std::pair<size_t, std::string> pageStartVar;  // Link page number with variable name
  std::pair<std::string, long int>
      pageStartVarValue;  // Link variable name with variable value
  std::pair<std::string, long int>
      choiceCondition;  // Link variable name with required value
  bool isStep4;

 public:
  ReadLine() : index(0), choice(0), isStep4(false) {}
  void initPage(std::string inputFile, std::vector<Page *> & pages);
  std::vector<std::string> readLine(std::string filename);  // Read file by line
  void printLine(std::string filename);                     // Print file content by line
  int parseLineType(std::string line);                      // Parse line type
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

class CheckPages {
 private:
  std::vector<std::size_t> pages;                  // Vector for all stored pages
  std::vector<std::vector<std::size_t> > choices;  // Choices for all pages
  bool checkedWinAndLose;                          // If to check exist win and lose page
  bool checkWin(std::string & type);               // Check contains win page
  bool checkLose(std::string & type);              // Check contains lose page

 public:
  CheckPages(std::vector<Page *> & pages);
  bool checkPages();
  bool checkChoices();
  bool getWinAndLoseStatus();
};

#endif
