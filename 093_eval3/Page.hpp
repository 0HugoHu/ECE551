#ifndef PAGE_HPP
#define PAGE_HPP

#include <cstdlib>
#include <vector>
#include <string>

class Page
{
private:
    size_t index;
    std::string pageName;

public:
    Page() : index(0) {}
    Page(const Page &it) : index(it.index), pageName(it.pageName) {}
    Page &operator=(const Page &it);
    size_t getIndex();
    std::string getPageName();
    virtual std::string getType() = 0;
    ~Page() {}
};

class NormalPage : public Page
{
private:
    std::vector<std::string> choice;
    std::vector<size_t> choiceGoto;
    static const std::string fixedString;

public:
    NormalPage() {}
    NormalPage(const NormalPage &it) : choice(it.choice), choiceGoto(it.choiceGoto) {}
    NormalPage &operator=(const NormalPage &it);
    std::string getType();
    void addChoice(std::string & line);
    ~NormalPage() {}
};

class WinPage : public Page
{
private:
    static const std::string fixedString;

public:
    std::string getType();
};

class LosePage : public Page
{
private:
    static const std::string fixedString;

public:
    std::string getType();
};

#endif