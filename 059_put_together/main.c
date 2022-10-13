#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * t = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Error open files!");
    exit(EXIT_FAILURE);
  }
  int length = 0;
  size_t size = 0;
  char * line = NULL;
  while ((length = getline(&line, &size, f)) != -1) {
    //printf("%s\n : %lu", line, strlen(line));
    line[strlen(line) - 1] = '\0';
    addCount(t, lookupValue(kvPairs, line));
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Cannot close file!");
    exit(EXIT_FAILURE);
  }
  return t;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "Input should have at least 3 arguments");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kvPairs = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts_t * c = countFile(argv[i], kvPairs);
    //   (call this result c)
    //compute the output file name from argv[i] (call this outName)
    const char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    if (f == NULL) {
      fprintf(stderr, "Error open files!");
      exit(EXIT_FAILURE);
    }
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Cannot close file!");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    //free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  free(kvPairs);

  return EXIT_SUCCESS;
}
