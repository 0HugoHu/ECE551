#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".count";
  int length = strlen(inputName) + 7;
  char * outputName = malloc(length * sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, suffix);
  return outputName;
}
