#include "Page.hpp"
#include "Tool.hpp"

std::size_t Page::pageNums = 0;
std::size_t Page::maxPageIndex = 0;
const std::string NormalPage::fixedString = "What would you like to do?\n";
const std::string WinPage::fixedString = "Congratulations! You have won. Hooray!";
const std::string LosePage::fixedString = "Sorry, you have lost. Better luck next time!";

Page &Page::operator=(const Page &it)
{
    this->index = it.index;
    this->pageName = it.pageName;
    return *this;
}

std::string Page::getType()
{
    return "Page";
}

std::size_t Page ::getIndex()
{
    return this->index;
}

std::string Page::getPageName()
{
    return this->pageName;
}

std::size_t Page::getPageNums()
{
    return this->pageNums;
}

std::size_t Page::getMaxPageIndex()
{
    return this->maxPageIndex;
}

void Page::incPageNums()
{
    this->pageNums++;
    this->updateMaxPageIndex(index);
}

void Page::updateMaxPageIndex(std::size_t index)
{
    this->maxPageIndex = index;
}

void Page::setIndex(std::size_t index)
{
    this->index = index;
}

void Page::setPageName(std::string name)
{
    this->pageName = name;
}

NormalPage &NormalPage::operator=(const NormalPage &it)
{
    this->choice = it.choice;
    this->choiceContent = it.choiceContent;
    return *this;
}

std::string NormalPage::getType()
{
    return "Normal";
}

void NormalPage::printPage(std::string prefix)
{
    ReadLine r;
    r.printLine(prefix + this->getPageName());
    std::cout << std::endl;
    std::cout << this->fixedString << std::endl;
    for (size_t i = 0; i < this->choiceContent.size(); i++)
    {
        std::cout << " " << i + 1 << ". " << choiceContent[i] << std::endl;
    }
}

void NormalPage::printPage(std::string prefix, std::vector<std::pair<size_t, std::string> > &varList, std::vector<std::pair<std::string, long int> > &varValList, std::vector<std::size_t> path)
{
    ReadLine r;
    r.printLine(prefix + this->getPageName());
    std::cout << std::endl;
    std::cout << this->fixedString << std::endl;
    for (size_t i = 0; i < this->choiceContent.size(); i++)
    {
        std::string var = getChoiceCondition()[i].first;
        long int val = getChoiceCondition()[i].second;
        if (var == "NO_CON" && val == 0)
        {
            std::cout << " " << i + 1 << ". " << choiceContent[i] << std::endl;
            continue;
        }
        else
        {
            size_t j = 0;
            long int vVal = 0;
            for (j = 0; j < varList.size(); j++)
            {
                // Found variable name
                if (varList[j].second == var)
                {
                    for (size_t k = 0; k < path.size(); k++) {
                        if (varList[j].first == path[k]) {
                            vVal = varValList[j].second;
                        }
                    }
                    if (val != vVal) {
                        std::cout << " " << i + 1 << ". <UNAVAILABLE>" << std::endl;
                        break;
                    } else {
                        std::cout << " " << i + 1 << ". " << choiceContent[i] << std::endl;
                        break;
                    }
                }
            }
            // No this variable name, but condition is 0
            if (j == 0 && val == 0)
            {
                std::cout << " " << i + 1 << ". " << choiceContent[i] << std::endl;
            }
        }
    }
}

void NormalPage::addChoice(std::size_t choice)
{
    this->choice.push_back(choice);
    this->choiceVisited.push_back(false);
}

void NormalPage::addChoiceContent(std::string choiceContent)
{
    this->choiceContent.push_back(choiceContent);
}

void NormalPage::addChoiceCondition(std::pair<std::string, long int> choiceCondition)
{
    this->choiceCondition.push_back(choiceCondition);
}

std::vector<std::pair<std::string, long int> > NormalPage::getChoiceCondition()
{
    return this->choiceCondition;
}

std::vector<std::size_t> NormalPage::getChoice()
{
    return this->choice;
}

std::vector<std::string> NormalPage::getChoiceContent()
{
    return this->choiceContent;
}

std::string WinPage::getType()
{
    return "Win";
}

void WinPage::printPage(std::string prefix)
{
    ReadLine r;
    // std::cout<<prefix + this->getPageName()<<std::endl;
    r.printLine(prefix + this->getPageName());
    std::cout << std::endl;
    std::cout << this->fixedString << std::endl;
}

void WinPage::printPage(std::string prefix, std::vector<std::pair<size_t, std::string> > &varList, std::vector<std::pair<std::string, long int> > &varValList, std::vector<std::size_t> path) {
    
}

void WinPage::addChoice(std::size_t choice)
{
}

void WinPage::addChoiceContent(std::string choiceContent)
{
}

void WinPage::addChoiceCondition(std::pair<std::string, long int> choiceCondition)
{
}

std::vector<std::size_t> WinPage::getChoice()
{
    std::vector<std::size_t> res;
    return res;
}

std::vector<std::string> WinPage::getChoiceContent()
{
    std::vector<std::string> res;
    return res;
}

std::vector<std::pair<std::string, long int> > WinPage::getChoiceCondition()
{
    std::vector<std::pair<std::string, long int> > res;
    return res;
}

std::string LosePage::getType()
{
    return "Lose";
}

void LosePage::printPage(std::string prefix)
{
    ReadLine r;
    // std::cout<<prefix + this->getPageName()<<std::endl;
    r.printLine(prefix + this->getPageName());
    std::cout << std::endl;
    std::cout << this->fixedString << std::endl;
}

void LosePage::printPage(std::string prefix, std::vector<std::pair<size_t, std::string> > &varList, std::vector<std::pair<std::string, long int> > &varValList, std::vector<std::size_t> path) {

}

void LosePage::addChoice(std::size_t choice)
{
}

void LosePage::addChoiceContent(std::string choiceContent)
{
}

void LosePage::addChoiceCondition(std::pair<std::string, long int> choiceCondition)
{
}

std::vector<std::pair<std::string, long int> > LosePage::getChoiceCondition()
{
    std::vector<std::pair<std::string, long int> > res;
    return res;
}

std::vector<std::size_t> LosePage::getChoice()
{
    std::vector<std::size_t> res;
    return res;
}

std::vector<std::string> LosePage::getChoiceContent()
{
    std::vector<std::string> res;
    return res;
}
