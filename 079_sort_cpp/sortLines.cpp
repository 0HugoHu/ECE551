#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sort_lines(std::istream & input) {
  if (input.eof() != 1 && input.good() != 1) {
    std::cerr << "Cannot open the file!" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string res;
  std::vector<std::string> lines;
  while (getline(input, res)) {
    lines.push_back(res);
  }

  std::sort(lines.begin(), lines.end());

  std::vector<std::string>::iterator it = lines.begin();

  while (it != lines.end()) {
    std::cout << *it++ << std::endl;
  }
}

void sort_file(int argc, char ** argv) {
  for (int i = 1; i < argc; i++) {
    std::ifstream input(argv[i], std::ifstream::in);
    if (!input.is_open()) {
      std::cerr << "Cannot open the file!" << std::endl;
      exit(EXIT_FAILURE);
    }
    sort_lines(input);
    input.close();
  }
}
int main(int argc, char ** argv) {
  if (argc == 1) {
    sort_lines(std::cin);
  }
  if (argc > 1) {
    sort_file(argc, argv);
  }

  return EXIT_SUCCESS;
}
