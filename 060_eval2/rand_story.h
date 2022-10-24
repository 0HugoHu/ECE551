#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdio.h>
#include <string.h>

//any functions you want your main to use

typedef int (* parseLineFunc) (char * line, ssize_t len, FILE * terminalFile);

void checkCmdArgs(int argc, int argcReq);

FILE * checkFile(const char * filePath, const char * permission);

void closeFile(FILE * f);

void readLines(FILE * f, parseLineFunc p, FILE * terminalFile);

#endif
