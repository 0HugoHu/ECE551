#include "rand_story.h"

#define REQUIRED_ARGC 1

/*
Function Pointer:
    Examine each line read, and replace "_*_" with "cat".
Arguments:
    line: char *, the line read from file, includes '\0' and '\n'
    len: ssize_t, the length of line read
    terminalFile: FILE *, the output file if needed
Return:
    0: Fail
    1: Success
*/
int replaceUnderscore(char * line, ssize_t len, FILE * terminalFile);

/*
todo...
*/
int main(int argc, char ** argv) {
    // Check command line arugments legality
    checkCmdArgs(argc, REQUIRED_ARGC + 1);

    // Check file name legality
    FILE *f = checkFile(argv[1], "r");

    // Read each line in file and execute repleacement
    readLines(f, replaceUnderscore, NULL);

    // Close file with error check
    closeFile(f);

    return EXIT_SUCCESS;
}


int replaceUnderscore(char * line, ssize_t len, FILE * terminalFile) {
    if (len < 1) {
        return 0;
    }

    // Result line, dynamic inits space with the length of the line
    char * result = malloc(len * sizeof(* result));

    // Length for result
    ssize_t j = 0;

    for (ssize_t i = 0; i < len; i++) {
        // Double realloc space
        if (j >= len) {
            result = realloc(result, 2 * j * sizeof(* result));
        }
        // If not "_", copy it to the result
        if (line[i] != '_') {
            result[j++] = line[i];
        }
        // Find "_", read until the next "_"
        else {
            ssize_t endIndex = i + 1;
            while (endIndex < len && line[endIndex] != '_') {
                endIndex++;
            }
            // No matching
            if (endIndex == len) {
                fprintf(stderr, "No matching \"_\" at the index of  %lu!\n", i);
                exit(EXIT_FAILURE);
            }
            // Find matching
            else {
                // Replace with "cat"
                result[j++] = 'c';
                result[j++] = 'a';
                result[j++] = 't';
                i = endIndex;
            }
        }
    }
    // Do not need to add '\0' and '\n' since *line contains them

    // Print result
    for (ssize_t i = 0; i < j; i++) {
        printf("%c", result[i]);
    }

    free(result);
    free(line);
    
    // Return success
    return 1;
}