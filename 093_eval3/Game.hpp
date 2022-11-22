#ifndef GAME_HPP
#define GAME_HPP

#include "Page.hpp"
#include "Tool.hpp"

class GamePlay
{
private:
    std::size_t curr;
    std::string directory;
    int readInput(size_t size);
    void backtracking(std::vector<std::string> &res, std::vector<Page *> &pages, size_t pageIndex, size_t choiceIndex, std::string ss);
    std::size_t getIndexByPageNum(std::vector<Page *> &pages, std::size_t num);

public:
    GamePlay(std::string dir) : curr(0), directory(dir) {}
    int play(std::vector<Page *> &pages);
    std::vector<std::string> findWinPath(std::vector<Page *> &pages);
    ~GamePlay() {}
};

#endif