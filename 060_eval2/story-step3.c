#include "rand_story.h"

#define REQUIRED_ARGC 2

/*
todo...
*/
int main(int argc, char ** argv) {
    // Check command line arugments legality
    checkCmdArgs(argc, REQUIRED_ARGC + 1);

    // Check file name legality
    FILE *dictionary = checkFile(argv[1], "r");
    FILE *template = checkFile(argv[2], "r");

    // Data structure to store the categories
    catarray_t * cats = malloc(sizeof(* cats));
    cats->arr = NULL;
    cats->n = 0;

    // Data structure to store the history
    catarray_t * history = malloc(sizeof(* history));
    history->arr = NULL;
    history->n = 0;

    // Read each line in file and store categories
    // readCategories is the function pointer
    readLines(dictionary, readCategories, "", cats, NULL);

    // Read each line in file and execute repleacement
    // replaceUnderscore is the function pointer
    readLines(template, replacement, "random", cats, history);

    // Close file with error check
    closeFile(dictionary);
    closeFile(template);

    // Free memory
    freeCats(cats);
    freeCats(history);

    return EXIT_SUCCESS;
}