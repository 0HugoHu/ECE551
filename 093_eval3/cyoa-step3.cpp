#include "Tool.hpp"
#include "Page.hpp"
#include "Game.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Input format: directory name contains the story.txt!" << std::endl;
        abort();
    }
    std::string directory(argv[1]);
    std::string inputFile = directory + "/story.txt";

    // Class ReadLine provides function to read content
    ReadLine r;
    std::vector<Page *> pages;
    // Load content and stored in vector
    r.initPage(inputFile, pages);

    // Check for page and choice ref
    CheckPages c(pages);
    if (!c.checkChoices() || !c.checkPages()) {
        std::cerr << "Reference: pages and choices must be referenced once!" << std::endl;
        abort();
    }

    // Check for win and lose page
    if (!c.getWinAndLoseStatus()) {
        std::cerr << "Win | Lose: Win and Lose page must exist!" << std::endl;
        abort();
    }

    // Find win paths
    GamePlay g(directory + "/");
    // Result pths
    std::vector<std::string> res = g.findWinPath(pages);

    // Print results
    for (size_t i = 0; i < res.size(); i++) {
        std::cout << res[i] << std::endl;
    }

    // Free memory
    for (size_t i = 0; i < pages.size(); i++)
    {
        delete pages[i];
    }
    pages.clear();

    return EXIT_SUCCESS;
}
