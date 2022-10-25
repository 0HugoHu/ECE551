#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <string.h>

#include "provided.h"

/*
errorMessage:
  Print error message based on error code, and
  exit the program.
Arguments:
  errorCode: int
  extra: size_t, additional arguments needed
Return:
  void
*/
void errorMessage(int errorCode, size_t extraArg);

/*
checkCmdArgs:
  Check if the given arguments are valid.
Arguments:
  argc: int
  argv: char **
  argcReq: int, arguments number required
  optionalReq: int, optional arguments number
Return:
  void
*/
void checkCmdArgs(int argc, char ** argv, int argcReq, int optionalReq);

/*
checkFile:
  Open the given file strem with error checking.
Arguments:
  f: FILE *
Return:
  void
*/
FILE * checkFile(const char * filePath, const char * permission);

/*
closeFile:
  Close the given file strem with error checking.
Arguments:
  f: FILE *
Return:
  void
*/
void closeFile(FILE * f);

/*
parseLineFunc - Function Pointer Base:
  Do different tasks in readLine function.
Arguments:
  line: char *
  len: ssize_t
  flag: char *
  cats: catarray_t *
  history: catarray_t *
Return:
  0: Fail
  1: Success
*/
typedef int (*parseLineFunc)(char * line,
                             ssize_t len,
                             char * flag,
                             catarray_t * cats,
                             catarray_t * history);

/*
replacement - Function Pointer:
  Examine each line read, and replace "_*_" with "cat".
Arguments:
  line: char *, the line read from file, includes '\0' and '\n'
  len: ssize_t, the length of line read
  flag: char *, replacement with "blank" or "random"
  cats: catarray_t *, store read data (not used in this func)
Return:
  0: Fail
  1: Success
*/
int replacement(char * line,
                ssize_t len,
                char * flag,
                catarray_t * cats,
                catarray_t * history);

/*
readCategories - Function Pointer:
    Parse each line read and store categories and items in catarray_t.
Arguments:
    line: char *, the line read from file, includes '\0' and '\n'
    len: ssize_t, the length of line read
    flag: char *, replacement with "blank", "random" or "unqiue"
    cats: catarray_t *, store read data (not used in this func)
Return:
    0: Fail
    1: Success
*/
int readCategories(char * line,
                   ssize_t len,
                   char * flag,
                   catarray_t * cats,
                   catarray_t * history);

/*
readLines:
  Read each line on given file stream, and execute
  specific function.
Arguments:
  f: FILE *
  func: parseLineFunc, function pointer
  flag: char *
    - "blank", "random", "unique"
  cats: catarray_t *, words list
  history: catarray_t *, previously replaced words
Return:
  void
*/
void readLines(FILE * f,
               parseLineFunc p,
               char * flag,
               catarray_t * cats,
               catarray_t * history);

/*
addCats:
  Add a key-value pair to the catarray_t data structure.
Arguments:
  cats: catarray_t *, words list
  key: char *
  value: const char *
Return:
  void
*/
void addCats(catarray_t * cats, char * key, const char * value);

/*
freeCats:
  Free allocated memory for data structure catarray_t.
Arguments:
  cats: catarray_t *
Return:
  void
*/
void freeCats(catarray_t * cats);

/*
containKey:
  Check if the given key is in word list.
Arguments:
  cats: catarray_t *, words list
  key: char *
Return:
  -1: not contains
  non -1: index of the key in cats
*/
int containKey(catarray_t * cats, char * key);

/*
containValue:
  Check if the given value is in word list.
Arguments:
  cats: catarray_t *, words list
  key: char *
  value: const char *
Return:
  NULL: contains
  non NULL: not contains, return the value
*/
char * containValue(catarray_t * cats, char * key, const char * value);

/*
replaceMode1:
  Simple replacement with "cat".
Arguments:
  result: char *
  index: ssize_t, index of result array
Return:
  index: ssize_t, updated index of result array
*/
int replaceMode1(char * result, ssize_t index);

/*
replaceMode2:
  Random replacement with unique words.
Arguments:
  result: char *
  index: ssize_t, index of result array
  cats: catarray_t *
  content: char *, category of requirement
  history: catarray_t *
Return:
  index: ssize_t, updated index of result array
*/
int replaceMode2(char * result,
                 ssize_t index,
                 catarray_t * cats,
                 char * content,
                 catarray_t * history);

/*
replaceMode3:
  Random replacement with not limits.
Arguments:
  result: char *
  index: ssize_t, index of result array
  cats: catarray_t *
  content: char *, category of requirement
  history: catarray_t *
Return:
  index: ssize_t, updated index of result array
*/
int replaceMode3(char * result,
                 ssize_t index,
                 catarray_t * cats,
                 char * content,
                 catarray_t * history);

/*
replaceMode4:
  Back reference replacement.
Arguments:
  result: char *
  index: ssize_t, index of result array
  history: catarray_t *
  content: char *, category of requirement
Return:
  index: ssize_t, updated index of result array
*/
int replaceMode4(char * result, ssize_t index, catarray_t * history, long content);

#endif
