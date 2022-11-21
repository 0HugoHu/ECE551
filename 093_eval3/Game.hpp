#ifndef GAME_HPP
#define GAME_HPP

#include "Page.hpp"
#include "Tool.hpp"

class GamePlay
{
private:
    std::size_t curr;
    std::string directory;
    int readInput();

public:
    GamePlay(std::string dir) : curr(0), directory(dir) {}
    int play(std::vector<Page *> &pages);
    ~GamePlay() {}
};

#endif