#include "Page.hpp"
#include "Tool.hpp"

#define DIRECTORY "/usr/local/ece551/cyoa/story1"

int main(int argc, char ** argv) {
  if (argc != 2) {
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

  // Print pages
  for (size_t i = 0; i < pages.size(); i++) {
    std::cout << "Page " << i << std::endl;
    std::cout << "==========" << std::endl;
    pages[i]->printPage(directory + "/");
    delete pages[i];
  }
  pages.clear();

  return EXIT_SUCCESS;
}
