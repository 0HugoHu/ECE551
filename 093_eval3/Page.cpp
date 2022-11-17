#include "Page.hpp"

static const NormalPage::fixedString = "What would you like to do?\n";
static const WinPage::fixedString = "Congratulations! You have won. Hooray!\n";
static const LosePage::fixedString = "Sorry, you have lost. Better luck next time!\n";


Page &Page::operator=(const Page &it)
{
    this->index = it.index;
    this->pageName = it.pageName;
}

size_t Page : getIndex()
{
    return index;
}

std::string Page::getPageName()
{
    return pageName;
}

NormalPage &NormalPage::operator=(const NormalPage &it)
{
    this->choice = it.choice;
    this->choiceGoto = it.choiceGoto;
}

std::string NormalPage::getType()
{
    return "Normal";
}

void NormalPage::addChoice(std::string & line) {
    
}

std::string WinPage::getType()
{
    return "Win";
}

std::string LosePage::getType()
{
    return "Lose";
}