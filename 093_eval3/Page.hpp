#ifndef PAGE_HPP
#define PAGE_HPP

#include <cstdlib>
#include <vector>
#include <string>
#include <utility> 

// Abstract Class for different kinds of pages
class Page
{
private:
    std::size_t index;
    std::string pageName;
    static std::size_t maxPageIndex;
    static std::size_t pageNums;
    void updateMaxPageIndex(size_t index);

public:
    Page() : index(0) {}
    Page(const Page &it) : index(it.index), pageName(it.pageName) {}
    Page &operator=(const Page &it);
    std::size_t getIndex();
    std::string getPageName();
    std::size_t getPageNums();
    std::size_t getMaxPageIndex();
    void incPageNums();
    void setIndex(std::size_t index);
    void setPageName(std::string name);
    std::vector<bool> choiceVisited;
    std::vector<std::pair<size_t, std::string> > varList;
    std::vector<std::pair<std::string, long int> > varValList;
    virtual std::string getType();
    virtual void printPage(std::string prefix) = 0;
    virtual void printPage(std::string prefix, std::vector<std::pair<size_t, std::string> > &varList, std::vector<std::pair<std::string, long int> > &varValList, std::vector<std::size_t> path) = 0;
    virtual void addChoice(std::size_t choice) = 0;
    virtual void addChoiceContent(std::string choiceContent) = 0;
    virtual void addChoiceCondition(std::pair<std::string, long int> choiceCondition) = 0;
    virtual std::vector<std::pair<std::string, long int> > getChoiceCondition() = 0;
    virtual std::vector<std::size_t> getChoice() = 0;
    virtual std::vector<std::string> getChoiceContent() = 0;
    virtual ~Page() {}
};

// Normal Page (N)
class NormalPage : public Page
{
private:
    std::vector<std::string> choiceContent;
    std::vector<std::size_t> choice;
    std::vector<std::pair<std::string, long int> > choiceCondition;
    static const std::string fixedString;

public:
    NormalPage() {}
    NormalPage(const NormalPage &it) : choiceContent(it.choiceContent), choice(it.choice) {}
    NormalPage &operator=(const NormalPage &it);
    virtual void addChoice(std::size_t choice);
    virtual void addChoiceContent(std::string choiceContent);
    virtual std::vector<std::size_t> getChoice();
    virtual std::vector<std::string> getChoiceContent();
    virtual void addChoiceCondition(std::pair<std::string, long int> choiceCondition);
    virtual std::vector<std::pair<std::string, long int> > getChoiceCondition();
    virtual std::string getType();
    virtual void printPage(std::string prefix);
    virtual void printPage(std::string prefix, std::vector<std::pair<size_t, std::string> > &varList, std::vector<std::pair<std::string, long int> > &varValList, std::vector<std::size_t> path);
    virtual ~NormalPage() {}
};

// Win Page (W)
class WinPage : public Page
{
private:
    static const std::string fixedString;

public:
    virtual std::string getType();
    virtual void printPage(std::string prefix);
    virtual void printPage(std::string prefix, std::vector<std::pair<size_t, std::string> > &varList, std::vector<std::pair<std::string, long int> > &varValList, std::vector<std::size_t> path);
    virtual void addChoice(std::size_t choice);
    virtual void addChoiceContent(std::string choiceContent);
    virtual void addChoiceCondition(std::pair<std::string, long int> choiceCondition);
    virtual std::vector<std::pair<std::string, long int> > getChoiceCondition();
    virtual std::vector<std::size_t> getChoice();
    virtual std::vector<std::string> getChoiceContent();
};

// Lose Page (L)
class LosePage : public Page
{
private:
    static const std::string fixedString;

public:
    virtual std::string getType();
    virtual void printPage(std::string prefix);
    virtual void printPage(std::string prefix, std::vector<std::pair<size_t, std::string> > &varList, std::vector<std::pair<std::string, long int> > &varValList, std::vector<std::size_t> path);
    virtual void addChoice(std::size_t choice);
    virtual void addChoiceContent(std::string choiceContent);
    virtual void addChoiceCondition(std::pair<std::string, long int> choiceCondition);
    virtual std::vector<std::pair<std::string, long int> > getChoiceCondition();
    virtual std::vector<std::size_t> getChoice();
    virtual std::vector<std::string> getChoiceContent();
};

#endif