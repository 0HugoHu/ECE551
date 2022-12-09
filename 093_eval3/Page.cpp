#include "Page.hpp"

#include "Tool.hpp"

std::size_t Page::pageNums = 0;     // Static variable for total page number
bool Page::isDelayStorage = false;  // Static variable for if delay storage
std::pair<size_t, std::string> Page::delayVar =
    std::make_pair(0, "");  // Static variable for delay storage
std::pair<std::string, long int> Page::delayVal =
    std::make_pair("", 0);  // Static variable for delay storage
const std::string NormalPage::fixedString =
    "What would you like to do?\n";  // Static const string for normal page
const std::string WinPage::fixedString =
    "Congratulations! You have won. Hooray!";  // Static const string for win page
const std::string LosePage::fixedString =
    "Sorry, you have lost. Better luck next time!";  // Static const string for lose page

// Assignment init
Page & Page::operator=(const Page & it) {
  this->index = it.index;
  this->pageName = it.pageName;
  return *this;
}

// Get page type
std::string Page::getType() {
  return "Page";
}

// Get page index
std::size_t Page ::getIndex() {
  return this->index;
}

// Get page name
std::string Page::getPageName() {
  return this->pageName;
}

// Get page number
std::size_t Page::getPageNums() {
  return this->pageNums;
}

// Increase page number by 1
void Page::incPageNums() {
  this->pageNums++;
}

// Set page index
void Page::setIndex(std::size_t index) {
  this->index = index;
}

// Set page name
void Page::setPageName(std::string name) {
  this->pageName = name;
}

// Assignment init
NormalPage & NormalPage::operator=(const NormalPage & it) {
  this->choice = it.choice;
  this->choiceContent = it.choiceContent;
  return *this;
}

// Get page type
std::string NormalPage::getType() {
  return "Normal";
}

// Print page (virtual function)
void NormalPage::printPage(std::string prefix) {
  ReadLine r;
  r.printLine(prefix + this->getPageName());
  std::cout << std::endl;
  std::cout << this->fixedString << std::endl;
  for (size_t i = 0; i < this->choiceContent.size(); i++) {
    std::cout << " " << i + 1 << ". " << choiceContent[i] << std::endl;
  }
}

// Print page (virtual function, overloaded)
void NormalPage::printPage(std::string prefix,
                           std::vector<std::pair<size_t, std::string> > & varList,
                           std::vector<std::pair<std::string, long int> > & varValList,
                           std::vector<std::pair<std::string, long int> > & umap) {
  ReadLine r;
  r.printLine(prefix + this->getPageName());
  std::cout << std::endl;
  std::cout << this->fixedString << std::endl;
  // Traversal each choice
  for (size_t i = 0; i < this->choiceContent.size(); i++) {
    std::string var = getChoiceCondition()[i].first;
    long int val = getChoiceCondition()[i].second;
    // If no condition choice
    if (var == "NO_CON" && val == 0) {
      std::cout << " " << i + 1 << ". " << choiceContent[i] << std::endl;
      continue;
    }
    else {
      size_t j = 0;
      // Find variable value in reverse order
      for (; j < umap.size(); j++) {
        if (umap[j].first == var) {
          if (umap[j].second == val) {
            std::cout << " " << i + 1 << ". " << choiceContent[i] << std::endl;
            break;
          }
          else {
            std::cout << " " << i + 1 << ". <UNAVAILABLE>" << std::endl;
            break;
          }
        }
      }
      if (j == umap.size() && val != 0) {
        std::cout << " " << i + 1 << ". <UNAVAILABLE>" << std::endl;
      }
      // No this variable name, but condition is 0
      else if (j == umap.size() && val == 0) {
        std::cout << " " << i + 1 << ". " << choiceContent[i] << std::endl;
      }
    }
  }
}

// Add choice
void NormalPage::addChoice(std::size_t choice) {
  this->choice.push_back(choice);
  this->choiceVisited.push_back(false);
}

// Add content of choice
void NormalPage::addChoiceContent(std::string choiceContent) {
  this->choiceContent.push_back(choiceContent);
}

// Add choice condition
void NormalPage::addChoiceCondition(std::pair<std::string, long int> choiceCondition) {
  this->choiceCondition.push_back(choiceCondition);
}

// Get condition choice
std::vector<std::pair<std::string, long int> > NormalPage::getChoiceCondition() {
  return this->choiceCondition;
}

// Get choice
std::vector<std::size_t> NormalPage::getChoice() {
  return this->choice;
}

// Get choice content
std::vector<std::string> NormalPage::getChoiceContent() {
  return this->choiceContent;
}

// Get page type
std::string WinPage::getType() {
  return "Win";
}

// Print page (virtual function)
void WinPage::printPage(std::string prefix) {
  ReadLine r;
  // std::cout<<prefix + this->getPageName()<<std::endl;
  r.printLine(prefix + this->getPageName());
  std::cout << std::endl;
  std::cout << this->fixedString << std::endl;
}

// Print page (virtual function, overloaded)
void WinPage::printPage(std::string prefix,
                        std::vector<std::pair<size_t, std::string> > & varList,
                        std::vector<std::pair<std::string, long int> > & varValList,
                        std::vector<std::pair<std::string, long int> > & umap) {
}

// Add choice (virtual function)
void WinPage::addChoice(std::size_t choice) {
}

// Add choice content (virtual function)
void WinPage::addChoiceContent(std::string choiceContent) {
}

// Add choice condition (virtual function)
void WinPage::addChoiceCondition(std::pair<std::string, long int> choiceCondition) {
}

// Get choice (virtual function)
std::vector<std::size_t> WinPage::getChoice() {
  std::vector<std::size_t> res;
  return res;
}

// Add choice content (virtual function)
std::vector<std::string> WinPage::getChoiceContent() {
  std::vector<std::string> res;
  return res;
}

// Get choice condition (virtual function)
std::vector<std::pair<std::string, long int> > WinPage::getChoiceCondition() {
  std::vector<std::pair<std::string, long int> > res;
  return res;
}

// Get page type (virtual function)
std::string LosePage::getType() {
  return "Lose";
}

// Print page (virtual function)
void LosePage::printPage(std::string prefix) {
  ReadLine r;
  // std::cout<<prefix + this->getPageName()<<std::endl;
  r.printLine(prefix + this->getPageName());
  std::cout << std::endl;
  std::cout << this->fixedString << std::endl;
}

// Print page (virtual function, overloaded)
void LosePage::printPage(std::string prefix,
                         std::vector<std::pair<size_t, std::string> > & varList,
                         std::vector<std::pair<std::string, long int> > & varValList,
                         std::vector<std::pair<std::string, long int> > & umap) {
}

// Add choice (virtual function)
void LosePage::addChoice(std::size_t choice) {
}

// Add choice content (virtual function)
void LosePage::addChoiceContent(std::string choiceContent) {
}

// Add choice condition (virtual function)
void LosePage::addChoiceCondition(std::pair<std::string, long int> choiceCondition) {
}

// Get choice condition (virtual function)
std::vector<std::pair<std::string, long int> > LosePage::getChoiceCondition() {
  std::vector<std::pair<std::string, long int> > res;
  return res;
}

// Get choice (virtual function)
std::vector<std::size_t> LosePage::getChoice() {
  std::vector<std::size_t> res;
  return res;
}

// Get choice content (virtual function)
std::vector<std::string> LosePage::getChoiceContent() {
  std::vector<std::string> res;
  return res;
}
