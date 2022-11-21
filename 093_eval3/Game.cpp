#include "Game.hpp"

int GamePlay::play(std::vector<Page *> &pages)
{
    std::string type = pages[this->curr]->getType();
    while (type == "Normal")
    {
        // Print current page
        pages[curr]->printPage(this->directory);
        size_t jumpTo = 0;
        // Continuelly read from user input
        do
        {
            jumpTo = this->readInput(pages[curr]->getChoice().size());
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