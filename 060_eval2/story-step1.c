#include "rand_story.h"

#define REQUIRED_ARGC 1

/*
story-step1:
  Replace all words begin and end with "_" with "cat".
Arguments:
  filename: char *, the story template to be executed
Output:
  stdout: multiple lines after the replacement
*/
int main(int argc, char ** argv) {
  // Check command line arugments legality
  checkCmdArgs(argc, argv, REQUIRED_ARGC + 1, REQUIRED_ARGC + 1);

  // Check file name legality
  FILE * f = checkFile(argv[1], "r");

  // Read each line in file and execute repleacement
  readLines(f, replacement, "blank", NULL, NULL);

  // Close file with error check
  closeFile(f);

  return EXIT_SUCCESS;
}
