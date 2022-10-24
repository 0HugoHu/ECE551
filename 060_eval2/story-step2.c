#include "rand_story.h"

#define REQUIRED_ARGC 1

/*
todo...
*/
int main(int argc, char ** argv) {
    // Check command line arugments legality
    checkCmdArgs(argc, REQUIRED_ARGC + 1);

    // Check file name legality
    FILE *f = checkFile(argv[1], "r");

    // Data structure to store the categories
    catarray_t * cats = malloc(sizeof(* cats));
    cats->arr = NULL;
    cats->n = 0;

    // Read each line in file and store categories
    // readCategories is the function pointer
    readLines(f, readCategories, "", cats, NULL);

    // Show results
    printWords(cats);

    // Close file with error check
    closeFile(f);

    // Free memory
    freeCats(cats);

    return EXIT_SUCCESS;
}
