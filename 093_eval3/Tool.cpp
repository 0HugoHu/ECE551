#include "Tool.hpp"
#include <string.h>
#include <errno.h>

int ReadLine::parseLineType(std::string line)
{
    std::size_t foundCol = line.find(":");
    std::size_t foundAt = line.find("@");

    std::size_t index = 0;
    int type = 0;

    // Choice Type
    // 2:1:Something
    if (foundCol != std::string::npos)
    {
        std::string segmentIndex = line.substr(0, foundCol);
        char *endptr;
        index = strtoul(segmentIndex.c_str(), &endptr, 10);
        if (!(endptr == segmentIndex.c_str() || *endptr != '\0' || index < 0))
        {
            this->index = index;

            std::string lineAfter = line.substr(foundCol + 1);
            std::size_t foundSecondCol = lineAfter.find(":");
            // choice (goto)
            if (foundSecondCol != std::string::npos)
            {
                std::string segmentChoice = lineAfter.substr(0, foundSecondCol);

                char *endptr2;
                index = strtoul(segmentChoice.c_str(), &endptr2, 10);
                if (!(endptr2 == segmentChoice.c_str() || *endptr2 != '\0' || index < 0))
                {
                    this->choice = index;

                    // Choice Content
                    std::string segmentChoiceContent = lineAfter.substr(foundSecondCol + 1);
                    if (segmentChoiceContent.size() != 0)
                    {
                        this->choiceContent = segmentChoiceContent;
                        return CHOICE;
                    }
                }
            }
        }
    }

    // Page Type
    // 0@N:page0.txt

    // Index
    if (foundAt != std::string::npos)
    {
        std::string segmentIndex = line.substr(0, foundAt);
        char *endptr;
        index = strtoul(segmentIndex.c_str(), &endptr, 10);
        if (endptr == segmentIndex.c_str() || *endptr != '\0' || index < 0)
        {
            return INVALID;
        }
        this->index = index;

        // Type
        std::size_t foundCol = line.find(":");
        if (foundCol != std::string::npos)
        {
            std::string segmentType = line.substr(foundAt + 1, foundCol - foundAt - 1);

            if (segmentType == "N")
            {
                type = NORMAL;
            }
            else if (segmentType == "W")
            {
                type = WIN;
            }
            else if (segmentType == "L")
            {
                type = LOSE;
            }
            else
            {
                return INVALID;
            }

            // File Name
            std::string segmentFileName = line.substr(foundCol + 1);
            std::size_t foundFile = segmentFileName.find(".txt");
            // Not contain ".txt"
            if (foundFile == std::string::npos || foundFile == 0)
            {
                return INVALID;
            }
            // std::cout<<segmentFileName<<std::endl;
            if (segmentFileName[segmentFileName.size() - 1] != 't')
            {
                segmentFileName[segmentFileName.size() - 1] = '\0';
            }
            this->pageName = segmentFileName;
            return type;
        }
        else
        {
            return INVALID;
        }
    }
    else
    {
        return INVALID;
    }

    return INVALID;
}

void ReadLine::initPage(std::string inputFile, std::vector<Page *> &pages)
{
    std::vector<std::string> lines = readLine(inputFile);
    for (size_t i = 0; i < lines.size(); i++)
    {
        // std::cout << lines[i] << std::endl;
        Page *page = new NormalPage();
        int type = parseLineType(lines[i]);
        // Page number must increasely declared

        if (page->getMaxPageIndex() != 0 && page->getMaxPageIndex() >= getIndex())
        {
            std::cerr << "Errors in story.txt!" << std::endl;
            abort();
        }

        switch (type)
        {
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

        case CHOICE:
        {
            if (0 == page->getPageNums())
            {
                std::cerr << "Errors in story.txt!" << std::endl;
                abort();
            }
            size_t j = 0;
            for (; j < page->getPageNums(); j++)
            {
                if (getIndex() == pages[j]->getIndex() && pages[j]->getType() == "Normal")
                {
                    pages[j]->addChoice(getChoice());
                    pages[j]->addChoiceContent(getChoiceContent());
                    break;
                }
            }
            // Must declare a page before jump
            if (j == pages[0]->getPageNums())
            {
                std::cerr << "Errors in story.txt!" << std::endl;
                abort();
            }
            break;
        }

        case INVALID:
        default:
            // Invalid format in story.txt
            std::cerr << "Errors in story.txt!" << std::endl;
            abort();
            break;
        }
        if (type != CHOICE)
        {
            page->incPageNums();
            page->setIndex(getIndex());
            page->setPageName(getPageName());
            pages.push_back(page);
        }
        else
        {
            delete page;
        }
    }
}

std::vector<std::string> ReadLine::readLine(std::string filename)
{
    std::ifstream f(filename.c_str());

    if (!f.is_open())
    {
        std::cerr << "Cannot open the file!" << std::endl;
        abort();
    }
    std::vector<std::string> res;
    std::string line;
    while (getline(f, line))
    {
        if (line != "\n" && line.size() >= 4)
        {
            res.push_back(line);
        }
    }
    f.close();

    return res;
}

void ReadLine::printLine(std::string filename)
{
    std::ifstream f(filename.c_str());
    if (!f.is_open())
    {
        std::cerr << "Cannot open the file!" << std::endl;
        abort();
    }
    std::string line;
    while (getline(f, line))
    {
        std::cout << line << std::endl;
    }
    f.close();
}

std::size_t ReadLine::getIndex()
{
    return this->index;
}

std::size_t ReadLine::getChoice()
{
    return this->choice;
}

std::string ReadLine::getPageName()
{
    return this->pageName;
}

std::string ReadLine::getChoiceContent()
{
    return this->choiceContent;
}

CheckPages::CheckPages(std::vector<Page *> &pages) : checkedWinAndLose(false)
{
    bool win = false;
    bool lose = false;
    size_t maxChoiceSize = 0;
    for (size_t i = 0; i < pages.size(); i++)
    {
        size_t num = pages[i]->getChoice().size();
        if (num > maxChoiceSize)
        {
            maxChoiceSize = num;
        }
    }

    maxChoiceSize += 2;

    for (size_t i = 0; i < pages.size(); i++)
    {
        this->pages.push_back(pages[i]->getIndex());
        std::string type = pages[i]->getType();
        if (!win)
        {
            win = this->checkWin(type);
        }
        if (!lose)
        {
            lose = this->checkLose(type);
        }
        if (type == "Normal")
        {
            std::vector<std::size_t> choice = pages[i]->getChoice();
            choice.push_back(RANDOM_NUM1);
            choice.push_back(RANDOM_NUM2);
            while (choice.size() < maxChoiceSize)
            {
                choice.push_back(0);
            }
            this->choices.push_back(choice);
        }
    }

    if (win && lose)
    {
        this->checkedWinAndLose = true;
    }
}

bool CheckPages::checkPages()
{
    if (pages.size() == 0)
    {
        return false;
    }
    for (size_t i = 1; i < pages.size(); i++)
    {
        // std::cout<<i<<std::endl;
        size_t page = pages[i];
        size_t j = 0;
        size_t k = 0;
        for (; j < choices.size(); j++)
        {
            k = 0;
            for (; choices[j][k] != RANDOM_NUM1 && choices[j][k + 1] != RANDOM_NUM2; k++)
            {
                if (choices[j][k] == page)
                    break;
            }
            if (choices[j][k] == page)
                break;
        }
        if (j == choices.size() && choices[j - 1][k] != RANDOM_NUM1 && choices[j - 1][k + 1] != RANDOM_NUM2)
        {
            return false;
        }
    }
    return true;
}

bool CheckPages::checkChoices()
{
    if (choices.size() == 0)
    {
        return false;
    }
    for (size_t i = 0; i < choices.size(); i++)
    {
        if (choices[i][0] == RANDOM_NUM1 && choices[i][2] == RANDOM_NUM2)
        {
            return false;
        }
        for (size_t j = 0; choices[i][j] != RANDOM_NUM1 && choices[i][j + 1] != RANDOM_NUM2; j++)
        {
            size_t page = choices[i][j];
            size_t k = 0;
            for (; k < pages.size(); k++)
            {
                if (page == pages[k])
                    break;
            }
            if (k == pages.size())
            {
                return false;
            }
        }
    }
    return true;
}

bool CheckPages::checkWin(std::string &type)
{
    return type == "Win";
}

bool CheckPages::checkLose(std::string &type)
{
    return type == "Lose";
}

bool CheckPages::getWinAndLoseStatus()
{
    return this->checkedWinAndLose;
}
