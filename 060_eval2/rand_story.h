#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdio.h>
#include <string.h>

//any functions you want your main to use

void checkCmdArgs(int argc, int argcReq);

FILE * checkFile(const char * filePath, const char * permission);

void closeFile(FILE * f);

typedef int (* parseLineFunc) (char * line, ssize_t len, char * flag, catarray_t * cats);

int replaceUnderscore(char * line, ssize_t len, char * flag, catarray_t * cats);

int readCategories(char * line, ssize_t len, char * flag, catarray_t * cats);

void readLines(FILE * f, parseLineFunc p, char * flag, catarray_t * cats);

void freeCats(catarray_t * cats);



#endif
