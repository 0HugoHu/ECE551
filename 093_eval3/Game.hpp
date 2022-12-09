#ifndef GAME_HPP
#define GAME_HPP

#include "Page.hpp"
#include "Tool.hpp"

class GamePlay {
 private:
  std::size_t curr;       // Current page
  std::string directory;  // Path to win
  int readInput(size_t size);
  void backtracking(std::vector<std::string> & res,
                    std::vector<Page *> & pages,
                    size_t pageIndex,
                    size_t choiceIndex,
                    std::string ss);
  std::size_t getIndexByPageNum(std::vector<Page *> & pages, std::size_t num);
  bool isStep4;                                         // Special rules in step 4
  std::vector<std::size_t> path;                        // All paths to win
  std::vector<std::pair<std::string, long int> > umap;  // Link choice with page number

 public:
  GamePlay(std::string dir) : curr(0), directory(dir), isStep4(false) {}
  size_t play(std::vector<Page *> & pages);  // Play the game
  std::vector<std::string> findWinPath(std::vector<Page *> & pages);
  void setIsStep4(bool b);
  void addPath(size_t page);
  long int getMap(std::string var);  // Get umap
  void putMap(std::string var, long int val);
  ~GamePlay() {}
};

#endif
