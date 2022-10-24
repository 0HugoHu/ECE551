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
