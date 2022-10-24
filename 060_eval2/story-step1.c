#include "rand_story.h"

#define REQUIRED_ARGC 1


/*
todo...
*/
int main(int argc, char ** argv) {
    // Check command line arugments legality
    checkCmdArgs(argc, argv, REQUIRED_ARGC + 1, REQUIRED_ARGC + 1);

    // Check file name legality
    FILE *f = checkFile(argv[1], "r");

    // Read each line in file and execute repleacement
    // replaceUnderscore is the function pointer
    readLines(f, replacement, "blank", NULL, NULL);

    // Close file with error check
    closeFile(f);

    return EXIT_SUCCESS;
}
