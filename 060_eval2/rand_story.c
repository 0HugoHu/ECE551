#include "rand_story.h"

void checkCmdArgs(int argc, int argcReq) {
    if (argc != argcReq) {
        fprintf(stderr, "Invalid command line arguments!\nFormat: %d arguments are required!", argcReq - 1);
        exit(EXIT_FAILURE);
    }
}

FILE * checkFile(const char * filePath, const char * permission) {
    FILE *f = fopen(filePath, permission);
    if (f == NULL) {
        fprintf(stderr, "Cannot open the file!\n");
        exit(EXIT_FAILURE);
    }

    return f;
}

void closeFile(FILE * f) {
    if (fclose(f) != 0) {
        fprintf(stderr, "Cannot close the file!\n");
        exit(EXIT_FAILURE);
    }
}


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
int replaceUnderscore(char * line, ssize_t len, FILE * terminalFile) {
    if (len < 1) {
        return 0;
    }

    // Result line, dynamic inits space with the length of the line
    char * result = malloc(len * sizeof(* result));

    // Length for result
    ssize_t j = 0;
    // Max size for result
    ssize_t jMax = len;

    for (ssize_t i = 0; i < len; i++) {
        // Check if realloc is needed
        if (j >= jMax - 1) {
            // Double realloc space
            result = realloc(result, 2 * (j + 1) * sizeof(* result));
            jMax = 2 * (j + 1);
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
                fprintf(stderr, "No matching \"_\" at the index of %lu!\n", i);
                exit(EXIT_FAILURE);
            }
            // Find matching
            else {
                // Replace with "cat"
                const char * replacement = chooseWord("blanks", NULL);
                for (ssize_t k = 0; k < strlen(replacement); k++) {
                    result[j++] = replacement[k];
                }
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

void readLines(FILE * f, parseLineFunc func, FILE * terminalFile) {
    char *line = NULL;
    size_t sz = 0;
    ssize_t lenRead;
    while ((lenRead = getline(&line, &sz, f)) != -1) {
        //todo...
        if (!func(line, lenRead, terminalFile)) {
            fprintf(stderr, "Something wrong in parseLineFunc!\n");
            exit(EXIT_FAILURE);
        }
        line = NULL;
    }
    free(line);
}
