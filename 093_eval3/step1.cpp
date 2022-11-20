#include "Tool.hpp"
#include "Page.hpp"


#define DIRECTORY "/usr/local/ece551/cyoa/story1"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Input format: directory name contains the story1.txt!" << std::endl;
    }
    std::string directory(argv[1]);
    std::string inputFile = directory + "/story.txt";

    std::vector<Page *> pages;
    ReadLine r;
    std::vector<std::string> lines = r.readLine(inputFile);
    for (size_t i = 0; i < lines.size(); i++)
    {
        
        Page *page = new NormalPage();
        int type = r.parseLineType(lines[i]);
        // Page number must increasely declared
       
        if (page->getMaxPageIndex() != 0 && page->getMaxPageIndex() >= r.getIndex())
        {
            std::cerr << "Errors in story.txt!" << std::endl;
        }

        switch (type)
        {
        case NORMAL:
            page = new NormalPage();
            break;
        case WIN:
            page = new WinPage();
            break;
        case LOSE:
            page = new LosePage();
            break;
        
        case CHOICE:
        {
            size_t j = 0;
            for (; j < page->getPageNums(); j++)
            {
                if (r.getIndex() == j && pages[j]->getType() == "Normal")
                {
                    pages[j]->addChoice(r.getChoice());
                    pages[j]->addChoiceContent(r.getChoiceContent());
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
            page->setIndex(r.getIndex());
            page->setPageName(r.getPageName());
            pages.push_back(page);
        }
    }

    for (size_t i = 0; i < pages.size(); i++)
    {
        std::cout << "Page " << i << std::endl;
        std::cout << "==========" << std::endl;
        pages[i]->printPage(directory + "/");
    }

    return 0;
}
