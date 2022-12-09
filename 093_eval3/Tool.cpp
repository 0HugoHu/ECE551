#include "Tool.hpp"

#include <errno.h>
#include <string.h>

// Parse each line in story.txt
// Return the line type
int ReadLine::parseLineType(std::string line) {
  std::size_t foundCol = line.find(":");
  std::size_t foundAt = line.find("@");
  std::size_t foundDollar = line.find("$");

  std::size_t index = 0;
  long int variableValue = 0;
  int type = 0;

  // Variable Type
  // 7$sword=1
  if (this->isStep4) {
    if (foundDollar != std::string::npos) {
      std::string segmentIndex = line.substr(0, foundDollar);
      char * endptr;
      index = strtoul(segmentIndex.c_str(), &endptr, 10);
      this->index = index;

      if (!(endptr == segmentIndex.c_str() || *endptr != '\0' || index < 0)) {
        std::string lineAfter = line.substr(foundDollar + 1);
        std::size_t foundEqaual = lineAfter.find("=");
        // variable name
        if (foundEqaual != std::string::npos) {
          std::string segmentVariableName = lineAfter.substr(0, foundEqaual);

          std::string lineLeft = lineAfter.substr(foundEqaual + 1);
          // variable value
          char * endptr2;
          variableValue = strtol(lineLeft.c_str(), &endptr2, 10);
          if (!(endptr2 == lineLeft.c_str() || *endptr2 != '\0')) {
            this->pageStartVar = std::make_pair(index, segmentVariableName);
            this->pageStartVarValue = std::make_pair(segmentVariableName, variableValue);
            return VARIABLE;
          }
        }
      }
    }
  }

  // Choice Type
  // 2:1:Something
  if (foundCol != std::string::npos) {
    std::string segmentIndex = line.substr(0, foundCol);
    char * endptr;
    index = strtoul(segmentIndex.c_str(), &endptr, 10);
    if (!(endptr == segmentIndex.c_str() || *endptr != '\0' || index < 0)) {
      this->index = index;

      std::string lineAfter = line.substr(foundCol + 1);
      std::size_t foundSecondCol = lineAfter.find(":");
      // choice (goto)
      if (foundSecondCol != std::string::npos) {
        std::string segmentChoice = lineAfter.substr(0, foundSecondCol);

        char * endptr2;
        index = strtoul(segmentChoice.c_str(), &endptr2, 10);
        if (!(endptr2 == segmentChoice.c_str() || *endptr2 != '\0' || index < 0)) {
          this->choice = index;

          // Choice Content
          std::string segmentChoiceContent = lineAfter.substr(foundSecondCol + 1);
          this->choiceContent = segmentChoiceContent;
          return CHOICE;
        }
      }
    }

    // Choice Condition
    // 8[broke=0]:10:Offer the dragon your last coins.
    else if (this->isStep4) {
      std::string pre = line.substr(0, foundCol);
      std::size_t foundLeftBracket = pre.find("[");

      if (foundLeftBracket != std::string::npos) {
        std::string segmentIndex = pre.substr(0, foundLeftBracket);
        char * endptr;
        index = strtoul(segmentIndex.c_str(), &endptr, 10);
        // index
        if (!(endptr == segmentIndex.c_str() || *endptr != '\0' || index < 0)) {
          this->index = index;

          segmentIndex = pre.substr(0, foundLeftBracket);
          std::size_t foundEqual = pre.find("=");
          if (foundEqual != std::string::npos) {
            // variable name
            std::string segmentVariableName =
                pre.substr(foundLeftBracket + 1, foundEqual - foundLeftBracket - 1);
            std::size_t foundRightBracket = pre.find("]");
            std::string segmentVariableValue =
                pre.substr(foundEqual + 1, foundRightBracket - foundEqual - 1);

            char * endptr2;
            long int value = strtoul(segmentVariableValue.c_str(), &endptr2, 10);
            // variable value
            if (!(endptr2 == segmentVariableValue.c_str() || *endptr2 != '\0')) {
              this->choiceCondition = std::make_pair(segmentVariableName, value);

              std::string lineAfter = line.substr(foundCol + 1);
              std::size_t foundSecondCol = lineAfter.find(":");
              // choice (goto)
              if (foundSecondCol != std::string::npos) {
                std::string segmentChoice = lineAfter.substr(0, foundSecondCol);

                char * endptr3;
                index = strtoul(segmentChoice.c_str(), &endptr3, 10);
                if (!(endptr3 == segmentChoice.c_str() || *endptr3 != '\0' ||
                      index < 0)) {
                  this->choice = index;

                  // Choice Content
                  std::string segmentChoiceContent = lineAfter.substr(foundSecondCol + 1);
                  this->choiceContent = segmentChoiceContent;
                  return CONDITION;
                }
              }
            }
          }
        }
      }
    }
  }

  // Page Type
  // 0@N:page0.txt

  // Index
  if (foundAt != std::string::npos) {
    std::string segmentIndex = line.substr(0, foundAt);
    char * endptr;
    index = strtoul(segmentIndex.c_str(), &endptr, 10);
    if (endptr == segmentIndex.c_str() || *endptr != '\0' || index < 0) {
      return INVALID;
    }
    this->index = index;

    // Type
    std::size_t foundCol = line.find(":");
    if (foundCol != std::string::npos) {
      std::string segmentType = line.substr(foundAt + 1, foundCol - foundAt - 1);

      if (segmentType == "N") {
        type = NORMAL;
      }
      else if (segmentType == "W") {
        type = WIN;
      }
      else if (segmentType == "L") {
        type = LOSE;
      }
      else {
        return INVALID;
      }

      // File Name
      std::string segmentFileName = line.substr(foundCol + 1);
      std::size_t foundFile = segmentFileName.find(".txt");
      // Not contain ".txt"
      if (foundFile == std::string::npos || foundFile == 0) {
        return INVALID;
      }
      // std::cout<<segmentFileName<<std::endl;
      if (segmentFileName[segmentFileName.size() - 1] != 't') {
        segmentFileName[segmentFileName.size() - 1] = '\0';
      }
      this->pageName = segmentFileName;
      return type;
    }
    else {
      return INVALID;
    }
  }
  else {
    return INVALID;
  }

  return INVALID;
}

// Add a new page with its type in pages vector
void ReadLine::initPage(std::string inputFile, std::vector<Page *> & pages) {
  std::vector<std::string> lines = readLine(inputFile);
  for (size_t i = 0; i < lines.size(); i++) {
    // std::cout << lines[i] << std::endl;
    Page * page = new NormalPage();
    int type = parseLineType(lines[i]);

    // Enable step 4 format
    if (!this->isStep4 && (type == VARIABLE || type == CONDITION)) {
      type = INVALID;
    }

    // Page number must in-orderly declared
    if (type == NORMAL || type == WIN || type == LOSE) {
      if (page->getPageNums() == 0 && getIndex() != 0) {
        std::cerr << "Errors in story.txt0!" << std::endl;
        abort();
      }
      if (page->getPageNums() != 0 && page->getPageNums() != getIndex()) {
        std::cerr << "Errors in story.txt1!" << std::endl;
        abort();
      }
    }

    switch (type) {
      case NORMAL:
        delete page;
        page = new NormalPage();
        break;
      case WIN:
        delete page;
        page = new WinPage();
        break;
      case LOSE:
        delete page;
        page = new LosePage();
        break;
      case VARIABLE: {
        // If page 0 exists
        if (0 == page->getPageNums()) {
          page->isDelayStorage = true;
          page->delayVar = this->getPageStartVar();
          page->delayVal = this->getPageStartVarValue();
        }
        // If not exist, store this variable for later storage
        else {
          pages[0]->varList.push_back(this->getPageStartVar());
          pages[0]->varValList.push_back(this->getPageStartVarValue());
        }

        break;
      }
      // In condition choice, the structure is similar with choice type
      case CONDITION:
      case CHOICE: {
        if (0 == page->getPageNums()) {
          std::cerr << "Errors in story.txt2!" << std::endl;
          abort();
        }
        size_t j = 0;
        for (; j < page->getPageNums(); j++) {
          if (getIndex() == pages[j]->getIndex() && pages[j]->getType() == "Normal") {
            pages[j]->addChoice(getChoice());
            pages[j]->addChoiceContent(getChoiceContent());
            // Only add conditions for choice in step 4
            if (this->isStep4) {
              if (type == CONDITION) {
                pages[j]->addChoiceCondition(getChoiceCondition());
              }
              else {
                std::pair<std::string, long int> tmp = std::make_pair("NO_CON", 0);
                pages[j]->addChoiceCondition(tmp);
              }
            }
            break;
          }
        }
        // Must declare a Normal page before jump
        if (j == pages[0]->getPageNums()) {
          std::cerr << "Errors in story.txt3!" << std::endl;
          abort();
        }
        break;
      }

      case INVALID:
      default:
        // Invalid format in story.txt
        std::cerr << "Errors in story.txt4!" << std::endl;
        abort();
        break;
    }
    // Only add this page if it is normal, win or lose
    if (type != CHOICE && type != VARIABLE && type != CONDITION) {
      page->incPageNums();
      page->setIndex(getIndex());
      page->setPageName(getPageName());
      pages.push_back(page);
      // If for later storage
      if (page->isDelayStorage) {
        pages[0]->varList.push_back(page->delayVar);
        pages[0]->varValList.push_back(page->delayVal);
      }
    }
    // Else delete this temp page
    else {
      delete page;
    }
  }
}

// Read file by line
std::vector<std::string> ReadLine::readLine(std::string filename) {
  std::ifstream f(filename.c_str());

  if (!f.is_open()) {
    std::cerr << "Cannot open the file!" << std::endl;
    abort();
  }
  std::vector<std::string> res;
  std::string line;
  while (getline(f, line)) {
    size_t index = 0;
    // Ignore line with all pain whitespaces
    if (line.size() > 0) {
      while (line[index++] == ' ')
        ;
    }
    // If this line is not empty, and has enough length, add to result
    if (index != line.size() && line != "\n" && line.size() >= 4) {
      res.push_back(line);
    }
  }
  f.close();

  return res;
}

// Print file by line
void ReadLine::printLine(std::string filename) {
  std::ifstream f(filename.c_str());
  if (!f.is_open()) {
    std::cerr << "Cannot open the file!" << std::endl;
    abort();
  }
  std::string line;
  while (getline(f, line)) {
    std::cout << line << std::endl;
  }
  f.close();
}

// Get current page index
std::size_t ReadLine::getIndex() {
  return this->index;
}

// Get current choice
std::size_t ReadLine::getChoice() {
  return this->choice;
}

// Get condition variable name
std::pair<size_t, std::string> ReadLine::getPageStartVar() {
  return this->pageStartVar;
}

// Get condition variable value
std::pair<std::string, long int> ReadLine::getPageStartVarValue() {
  return this->pageStartVarValue;
}

// Get condition choice
std::pair<std::string, long int> ReadLine::getChoiceCondition() {
  return this->choiceCondition;
}

// Get page name
std::string ReadLine::getPageName() {
  return this->pageName;
}

// Get choice content
std::string ReadLine::getChoiceContent() {
  return this->choiceContent;
}

// Check if in step4
void ReadLine::setIsStep4(bool b) {
  this->isStep4 = b;
}

// Check if pages all meet requirements
CheckPages::CheckPages(std::vector<Page *> & pages) : checkedWinAndLose(false) {
  // Contains win or lose page
  bool win = false;
  bool lose = false;
  size_t maxChoiceSize = 0;

  // Get the maximum choice size
  for (size_t i = 0; i < pages.size(); i++) {
    size_t num = pages[i]->getChoice().size();
    if (num > maxChoiceSize) {
      maxChoiceSize = num;
    }
  }

  // Add two extra spaces for random number
  // to mark as the end
  maxChoiceSize += 2;

  // Find if contains win and lose page
  for (size_t i = 0; i < pages.size(); i++) {
    this->pages.push_back(pages[i]->getIndex());
    std::string type = pages[i]->getType();
    if (!win) {
      win = this->checkWin(type);
    }
    if (!lose) {
      lose = this->checkLose(type);
    }
    if (type == "Normal") {
      std::vector<std::size_t> choice = pages[i]->getChoice();
      // Set the end of vector of fixed size
      choice.push_back(RANDOM_NUM1);
      choice.push_back(RANDOM_NUM2);
      while (choice.size() < maxChoiceSize) {
        choice.push_back(0);
      }
      this->choices.push_back(choice);
    }
  }

  if (win && lose) {
    this->checkedWinAndLose = true;
  }
}

// Check pages dependents
bool CheckPages::checkPages() {
  // No page return error
  if (pages.size() == 0) {
    return false;
  }

  // Check if each page is referenced
  for (size_t i = 1; i < pages.size(); i++) {
    // std::cout<<i<<std::endl;
    size_t page = pages[i];
    size_t j = 0;
    size_t k = 0;
    for (; j < choices.size(); j++) {
      k = 0;
      for (; choices[j][k] != RANDOM_NUM1 && choices[j][k + 1] != RANDOM_NUM2; k++) {
        if (choices[j][k] == page)
          break;
      }
      if (choices[j][k] == page)
        break;
    }
    // Exist one page that is not found to be referenced
    if (j == choices.size() && choices[j - 1][k] != RANDOM_NUM1 &&
        choices[j - 1][k + 1] != RANDOM_NUM2) {
      return false;
    }
  }
  return true;
}

//Check choices dependents
bool CheckPages::checkChoices() {
  // No choice for each page, allowed
  if (choices.size() == 0) {
    return true;
  }

  // Check if each choice is recheable
  for (size_t i = 0; i < choices.size(); i++) {
    if (choices[i][0] == RANDOM_NUM1 && choices[i][1] == RANDOM_NUM2) {
      return false;
    }
    for (size_t j = 0; choices[i][j] != RANDOM_NUM1 && choices[i][j + 1] != RANDOM_NUM2;
         j++) {
      size_t page = choices[i][j];
      size_t k = 0;
      for (; k < pages.size(); k++) {
        if (page == pages[k])
          break;
      }
      if (k == pages.size()) {
        return false;
      }
    }
  }
  return true;
}

// Return page type
bool CheckPages::checkWin(std::string & type) {
  return type == "Win";
}

// Return page type
bool CheckPages::checkLose(std::string & type) {
  return type == "Lose";
}

// Return check status
bool CheckPages::getWinAndLoseStatus() {
  return this->checkedWinAndLose;
}
