#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  int length = strlen(inputName) + 8;
  char * outputName = malloc(length * sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, suffix);
  return outputName;
}
