#include "Game.hpp"

size_t GamePlay::play(std::vector<Page *> &pages)
{
    std::string type = pages[this->curr]->getType();
    while (type == "Normal")
    {
        this->addPath(curr);

        // Add variable
        for (size_t i = 0; i < pages[0]->varList.size(); i++) {
            if (pages[0]->varList[i].first == curr) {
                size_t j = 0;
                for (; j < this->umap.size(); j++) {
                    // Var exists, update value
                    if (this->umap[j].first == pages[0]->varList[i].second) {
                        this->umap[j].second = pages[0]->varValList[i].second;
                        break;
                    }
                }
                // Add new variable
                if (j == this->umap.size()) {
                    this->putMap(pages[0]->varValList[i].first, pages[0]->varValList[i].second);
                }
            }
        }

        // Print current page
        if (isStep4)
        {
            pages[curr]->printPage(this->directory, pages[0]->varList, pages[0]->varValList, umap);
        }
        else
        {
            pages[curr]->printPage(this->directory);
        }

        size_t jumpTo = 0;
        // Continuelly read from user input
        do
        {
            jumpTo = this->readInput(pages[curr]->getChoice().size());
            if (isStep4) {
                std::string var = pages[curr]->getChoiceCondition()[jumpTo - 1].first;
                long int val = pages[curr]->getChoiceCondition()[jumpTo - 1].second;

                size_t j = 0;
                for (; j < umap.size(); j++)
                {
                    if (umap[j].first == var && umap[j].second == val)
                    {
                        break;
                    }
                }
                if (j == umap.size() && val != 0) {
                    std::cout << "That choice is not available at this time, please try again" << std::endl;
                    jumpTo = 0;
                } 
            }
                           
        } while (jumpTo == 0);

        // Jump to another page
        this->curr = pages[curr]->getChoice()[jumpTo - 1];
        type = pages[this->curr]->getType();
    }

    // Return result page index
    return curr;
}

int GamePlay::readInput(size_t size)
{
    size_t read = 0;
    std::string line;
    std::getline(std::cin, line);

    char *endptr;
    read = strtoul(line.c_str(), &endptr, 10);
    if (endptr == line.c_str() || *endptr != '\0' || read <= 0 || read > size)
    {
        std::cout << "That is not a valid choice, please try again" << std::endl;
        read = 0;
    }

    return read;
}

void GamePlay::setIsStep4(bool b)
{
    this->isStep4 = b;
}

std::vector<std::string> GamePlay::findWinPath(std::vector<Page *> &pages)
{
    std::vector<std::string> res;
    this->backtracking(res, pages, 0, 0, "");
    return res;
}

void GamePlay::backtracking(std::vector<std::string> &res, std::vector<Page *> &pages, size_t pageIndex, size_t choiceIndex, std::string s)
{
    if (pages[pageIndex]->getType() == "Win")
    {
        std::stringstream ss;
        ss << pages[pageIndex]->getIndex();
        s += (ss.str() + "(win)");
        res.push_back(s);
    }

    if (pages[pageIndex]->getChoice().size() == 0 || pages[pageIndex]->choiceVisited[choiceIndex])
    {
        return;
    }

    // Mark current node as visited
    pages[pageIndex]->choiceVisited[choiceIndex] = true;

    // Traveral all pages and choices

    for (size_t j = 0; j < pages[pageIndex]->getChoice().size(); j++)
    {
        std::stringstream ss, ss2;
        ss << pages[pageIndex]->getIndex();
        ss2 << j + 1;
        backtracking(res, pages, this->getIndexByPageNum(pages, pages[pageIndex]->getChoice()[j]), 0, s + ss.str() + "(" + ss2.str() + "),");
    }

    // Mark current node as visited
    pages[pageIndex]->choiceVisited[choiceIndex] = false;
}

std::size_t GamePlay::getIndexByPageNum(std::vector<Page *> &pages, std::size_t num)
{
    for (size_t i = 0; i < pages.size(); i++)
    {
        if (pages[i]->getIndex() == num)
        {
            return i;
        }
    }
    return 0;
}

void GamePlay::addPath(size_t page)
{
    this->path.push_back(page);
}

long int GamePlay::getMap(std::string var)
{
    for (size_t i = 0; i < umap.size(); i++) {
        if (umap[i].first == var) {
            return umap[i].second;
        }
    }
    return -1;
}
void GamePlay::putMap(std::string var, long int val)
{
    std::pair<std::string, long int> tmp = std::make_pair(var, val);
    this->umap.push_back(tmp);
}
