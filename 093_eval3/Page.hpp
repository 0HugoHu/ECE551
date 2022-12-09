#ifndef PAGE_HPP
#define PAGE_HPP

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

// Abstract Class for different kinds of pages
class Page {
 private:
  std::size_t index;            // Page index
  std::string pageName;         // Page file name
  static std::size_t pageNums;  // Total page number

 public:
  Page() : index(0) {}
  Page(const Page & it) : index(it.index), pageName(it.pageName) {}
  Page & operator=(const Page & it);
  std::size_t getIndex();
  std::string getPageName();
  std::size_t getPageNums();
  void incPageNums();
  void setIndex(std::size_t index);
  void setPageName(std::string name);
  std::vector<bool> choiceVisited;                            // Mark choice as visited
  static bool isDelayStorage;                                 // Is delay storage
  static std::pair<size_t, std::string> delayVar;             // Is delay storage
  static std::pair<std::string, long int> delayVal;           // Is delay storage
  std::vector<std::pair<size_t, std::string> > varList;       // Is delay storage
  std::vector<std::pair<std::string, long int> > varValList;  // Is delay storage
  virtual std::string getType();                   // virtual function, get page type
  virtual void printPage(std::string prefix) = 0;  // virtual function, print page
  virtual void printPage(std::string prefix,
                         std::vector<std::pair<size_t, std::string> > & varList,
                         std::vector<std::pair<std::string, long int> > & varValList,
                         std::vector<std::pair<std::string, long int> > & umap) = 0;
  virtual void addChoice(std::size_t choice) = 0;  // virtual function, add choice
  virtual void addChoiceContent(
      std::string choiceContent) = 0;  // virtual function, add choice content
  virtual void addChoiceCondition(
      std::pair<std::string, long int>
          choiceCondition) = 0;  // virtual function, add choice condition
  virtual std::vector<std::pair<std::string, long int> >
  getChoiceCondition() = 0;  // virtual function, get choice condition
  virtual std::vector<std::size_t> getChoice() = 0;  // virtual function, get choice
  virtual std::vector<std::string>
  getChoiceContent() = 0;  // virtual function, get choice content
  virtual ~Page() {}
};

// Normal Page (N)
class NormalPage : public Page {
 private:
  std::vector<std::string> choiceContent;  // Choice content for all possible choices
  std::vector<std::size_t> choice;         // Choice jumpTo for all possible choices
  std::vector<std::pair<std::string, long int> >
      choiceCondition;                   // Choice condition for all possible choices
  static const std::string fixedString;  // Print const string

 public:
  NormalPage() {}
  NormalPage(const NormalPage & it) :
      choiceContent(it.choiceContent), choice(it.choice) {}
  NormalPage & operator=(const NormalPage & it);
  virtual void addChoice(std::size_t choice);
  virtual void addChoiceContent(std::string choiceContent);
  virtual std::vector<std::size_t> getChoice();
  virtual std::vector<std::string> getChoiceContent();
  virtual void addChoiceCondition(std::pair<std::string, long int> choiceCondition);
  virtual std::vector<std::pair<std::string, long int> > getChoiceCondition();
  virtual std::string getType();
  virtual void printPage(std::string prefix);
  virtual void printPage(std::string prefix,
                         std::vector<std::pair<size_t, std::string> > & varList,
                         std::vector<std::pair<std::string, long int> > & varValList,
                         std::vector<std::pair<std::string, long int> > & umap);
  virtual ~NormalPage() {}
};

// Win Page (W)
class WinPage : public Page {
 private:
  static const std::string fixedString;  // Print const string

 public:
  virtual std::string getType();
  virtual void printPage(std::string prefix);
  virtual void printPage(std::string prefix,
                         std::vector<std::pair<size_t, std::string> > & varList,
                         std::vector<std::pair<std::string, long int> > & varValList,
                         std::vector<std::pair<std::string, long int> > & umap);
  virtual void addChoice(std::size_t choice);
  virtual void addChoiceContent(std::string choiceContent);
  virtual void addChoiceCondition(std::pair<std::string, long int> choiceCondition);
  virtual std::vector<std::pair<std::string, long int> > getChoiceCondition();
  virtual std::vector<std::size_t> getChoice();
  virtual std::vector<std::string> getChoiceContent();
};

// Lose Page (L)
class LosePage : public Page {
 private:
  static const std::string fixedString;  // Print const string

 public:
  virtual std::string getType();
  virtual void printPage(std::string prefix);
  virtual void printPage(std::string prefix,
                         std::vector<std::pair<size_t, std::string> > & varList,
                         std::vector<std::pair<std::string, long int> > & varValList,
                         std::vector<std::pair<std::string, long int> > & umap);
  virtual void addChoice(std::size_t choice);
  virtual void addChoiceContent(std::string choiceContent);
  virtual void addChoiceCondition(std::pair<std::string, long int> choiceCondition);
  virtual std::vector<std::pair<std::string, long int> > getChoiceCondition();
  virtual std::vector<std::size_t> getChoice();
  virtual std::vector<std::string> getChoiceContent();
};

#endif
