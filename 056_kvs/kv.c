#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "File does not exist!");
    exit(EXIT_FAILURE);
  }

  kvarray_t * t = malloc(sizeof(*t));
  t->data = NULL;
  t->length = 0;

  char * line = NULL;
  size_t size = 0;
  int num = 0;
  int divider = 0;

  while ((num = getline(&line, &size, f)) != -1) {
    int is_valid = 0;
    for (int i = 0; i < num; i++) {
      if (line[i] == '=') {
        if (i == 0 || i == num - 1) {
          fprintf(stderr, "Illegal line data!");
          exit(EXIT_FAILURE);
        }
        divider = i;
        is_valid = 1;
        break;
      }
    }
    if (!is_valid) {
      fprintf(stderr, "Illegal line data!");
      exit(EXIT_FAILURE);
    }
    //printf("%s, %d\n", line, divider);
    kvpair_t * pair = malloc(sizeof(*pair));
    pair->key = malloc((divider + 1) * sizeof(*pair->key));
    pair->value = malloc((num - divider) * sizeof(*pair->value));

    strncpy(pair->key, line, divider);
    pair->key[divider] = '\0';
    strncpy(pair->value, line + divider + 1, num - divider - 1);
    pair->value[num - divider - 1] = '\0';

    //printf("key = '%s' value = '%s'\n", pair->key, pair->value);
    t->data = realloc(t->data, (t->length + 1) * sizeof(*t->data));
    t->data[t->length] = pair;
    t->length++;
  }

  free(line);

  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing the file!");
    exit(EXIT_FAILURE);
  }

  return t;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (unsigned i = 0; i < pairs->length; i++) {
    free(pairs->data[i]->key);
    free(pairs->data[i]->value);
    free(pairs->data[i]);
  }
  free(pairs->data);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (unsigned i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->data[i]->key, pairs->data[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (unsigned i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->data[i]->key, key) == 0) {
      return pairs->data[i]->value;
    }
  }
  return NULL;
}
