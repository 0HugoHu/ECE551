#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdio.h>
#include <string.h>

//any functions you want your main to use

void checkCmdArgs(int argc, char ** argv, int argcReq, int optionalReq);

FILE * checkFile(const char * filePath, const char * permission);

void closeFile(FILE * f);

typedef int (* parseLineFunc) (char * line, ssize_t len, char * flag, catarray_t * cats, catarray_t * history);

int replacement(char * line, ssize_t len, char * flag, catarray_t * cats, catarray_t * history);

int readCategories(char * line, ssize_t len, char * flag, catarray_t * cats, catarray_t * history);

void readLines(FILE * f, parseLineFunc p, char * flag, catarray_t * cats, catarray_t * history);

void addCats(catarray_t * cats, char * key, const char * value);

void freeCats(catarray_t * cats);

int containKey(catarray_t * cats, char * key);

char * containValue(catarray_t * cats, char * key, const char * value);



#endif
