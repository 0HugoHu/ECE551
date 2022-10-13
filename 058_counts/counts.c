#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * t = malloc(sizeof(*t));
  t->array = NULL;
  t->length = 0;
  t->unknown.num = 0;
  t->unknown.string = NULL;
  return t;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown.num++;
    return;
  }
  for (int i = 0; i < c->length; i++) {
    if (strcmp(c->array[i]->string, name) == 0) {
      c->array[i]->num++;
      return;
    }
  }

  c->length++;
  c->array = realloc(c->array, c->length * sizeof(*c->array));
  c->array[c->length - 1] = malloc(sizeof(*c->array[c->length - 1]));
  c->array[c->length - 1]->num = 1;
  c->array[c->length - 1]->string =
      malloc((strlen(name) + 1) * sizeof(*c->array[c->length - 1]->string));
  strcpy(c->array[c->length - 1]->string, name);
  c->array[c->length - 1]->string[strlen(name)] = '\0';
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (outFile == NULL) {
    fprintf(stderr, "Cannot open output file!");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < c->length; i++) {
    fprintf(outFile, "%s: %d\n", c->array[i]->string, c->array[i]->num);
  }
  if (c->unknown.num != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknown.num);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    free(c->array[i]->string);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
