#include "rand_story.h"

#define UNIQUE_TAG "eHA2WXcRupyKT4dC"

void checkCmdArgs(int argc, int argcReq) {
  if (argc != argcReq) {
    fprintf(stderr,
            "Invalid command line arguments!\nFormat: %d arguments are required!",
            argcReq - 1);
    exit(EXIT_FAILURE);
  }
}

FILE * checkFile(const char * filePath, const char * permission) {
  FILE * f = fopen(filePath, permission);
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

/*
Function Pointer:
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
int replacement(char * line, ssize_t len, char * flag, catarray_t * cats, catarray_t * history) {
  // Check mode: 1 - blank, 0 - random
  int mode = !strcmp(flag, "blank");

  // Result line, dynamic inits space with the length of the line
  char * result = malloc(len * sizeof(*result));

  // Length for result
  ssize_t j = 0;
  // Max size for result
  ssize_t jMax = len;

  for (ssize_t i = 0; i < len; i++) {
    // Check if realloc is needed
    if (j >= jMax - 1) {
      // Double realloc space
      result = realloc(result, 2 * (j + 1) * sizeof(*result));
      jMax = 2 * (j + 1);
    }
    // If not "_", copy it to the result
    if (line[i] != '_') {
      result[j++] = line[i];
    }
    // Find "_", read until the next "_"
    else {
      ssize_t endIndex = i + 1;
      while (endIndex < len && line[endIndex] != '_') {
        endIndex++;
      }
      // No matching
      if (endIndex == len) {
        fprintf(stderr, "No matching \"_\" at the index of %lu!\n", i);
        exit(EXIT_FAILURE);
      }
      // Find matching
      else {
        // Replace with "cat"
        if (mode) {
          const char * replacement = chooseWord(flag, NULL);
          for (ssize_t k = 0; k < strlen(replacement); k++) {
            result[j++] = replacement[k];
          }
          i = endIndex;
        }
        // Replace with random words
        else {
          // Check if it is in category first
          char *content = malloc((endIndex - i) * sizeof(* content));
          strncpy(content, line + i + 1, endIndex - i - 1);
          content[endIndex - i - 1] = '\0';

          int index = containKey(cats, content);
          // Try to convert to a number
          char *endptr;
          long number = strtol(content, &endptr, 10);
          // Simple replacement
          if (index != -1) {
            const char * replacement = chooseWord(content, cats);
            for (ssize_t k = 0; k < strlen(replacement); k++) {
              result[j++] = replacement[k];
            }
            i = endIndex;
            char *tag = "eHA2WXcRupyKT4dC";
            addCats(history, tag, replacement);
          } 
          // Back reference
          else if (*endptr == '\0' && number > 0) {
            // If first a reference, rejects
            if (history->n == 0) {
              fprintf(stderr, "Back reference should not be the start!\n");
              exit(EXIT_FAILURE);
            }
            // If reference number larger than size, rejects
            if (number > history->arr[0].n_words) {
              fprintf(stderr, "Back reference goes beyond boundary!\n");
              exit(EXIT_FAILURE);
            }
            const char * replacement = history->arr[0].words[history->arr[0].n_words - number];
            for (ssize_t k = 0; k < strlen(replacement); k++) {
              result[j++] = replacement[k];
            }
            i = endIndex;
            char *tag = "eHA2WXcRupyKT4dC";
            addCats(history, tag, replacement);
          } 
          // Not in category
          else {
            fprintf(stderr, "Required key does not exist!\n");
            exit(EXIT_FAILURE);
          }
          free(content);

        }
      }
    }
  }

  // Print result
  for (ssize_t i = 0; i < j; i++) {
    printf("%c", result[i]);
  }

  free(result);
  free(line);
  return 1;
}

int containKey(catarray_t * cats, char * key) {
  for (size_t i = 0; i < cats->n; i++) {
    if (!strcmp(key, cats->arr[i].name)) {
      return i;
    }
  }
  return -1;
}


void addCats(catarray_t * cats, char * key, const char * value) {
  int index = containKey(cats, key);
  // Found category name and add new items
  if (index != -1) {
    // Same value exists
    /*
    for (size_t i = 0; i < cats->arr[index].n_words; i++) {
      if (!strcmp(cats->arr[index].words[i], value)) {
        return 1;
      }
    }
    */
    cats->arr[index].words = realloc(
          cats->arr[index].words, (cats->arr[index].n_words + 1) * sizeof(*cats->arr[index].words));

    cats->arr[index].words[cats->arr[index].n_words] = malloc((strlen(value) + 1) * sizeof(*cats->arr[index].words[cats->arr[index].n_words]));
    strncpy(cats->arr[index].words[cats->arr[index].n_words], value, strlen(value));
    cats->arr[index].words[cats->arr[index].n_words][strlen(value)] = '\0';

    cats->arr[index].n_words++;
  }
  
  // No category name matches, create new one
  cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));

  cats->arr[cats->n].name = malloc((strlen(key) + 1) * sizeof(*cats->arr[cats->n].name));
  strncpy(cats->arr[cats->n].name, key, strlen(key));
  cats->arr[cats->n].name[strlen(key)] = '\0';

  cats->arr[cats->n].words = malloc(sizeof(*cats->arr[cats->n].words));

  cats->arr[cats->n].words[0] = malloc((strlen(value) + 1) * sizeof(*cats->arr[cats->n].words[0]));
  strncpy(cats->arr[cats->n].words[0], value, strlen(value));
  cats->arr[cats->n].words[0][strlen(value)] = '\0';

  cats->arr[cats->n].n_words = 1;
  cats->n++;
}

/*
Function Pointer:
    Parse each line read and store categories and items in catarray_t.
Arguments:
    line: char *, the line read from file, includes '\0' and '\n'
    len: ssize_t, the length of line read
    flag: char *, replacement with "blank" or "random"
    cats: catarray_t *, store read data (not used in this func)
Return:
    0: Fail
    1: Success
*/
int readCategories(char * line, ssize_t len, char * flag, catarray_t * cats, catarray_t * history) {
  // Find the colon
  char * valuePtr = strchr(line, ':');
  // If not find colon
  if (valuePtr == NULL) {
    fprintf(stderr, "Invalid line read! Must be in key:value format!\n");
    exit(EXIT_FAILURE);
  }

  int lenKey = valuePtr - line;
  // If key length of 0
  if (lenKey <= 0) {
    fprintf(stderr, "Key name must be at least one character long!\n");
    exit(EXIT_FAILURE);
  }

  // Seperate key and value
  char * key = strndup(line, lenKey);
  char * value = strndup(valuePtr + 1, len - 1 - (lenKey + 1));

  // Found category name and add new items
  addCats(cats, key, value);
  free(key);
  free(value);
  free(line);
  return 1;
}

void readLines(FILE * f, parseLineFunc func, char * flag, catarray_t * cats, catarray_t * history) {
  char * line = NULL;
  size_t sz = 0;
  ssize_t lenRead;
  while ((lenRead = getline(&line, &sz, f)) != -1) {
    //todo...
    if (sz < 1 || !func(line, lenRead, flag, cats, history)) {
      fprintf(stderr, "Something wrong in parseLineFunc!\n");
      exit(EXIT_FAILURE);
    }
    line = NULL;
  }
  free(line);
}

void freeCats(catarray_t * cats) {
  if (cats == NULL) {
    return;
  }

  for (size_t i = 0; i < cats->n; i++) {
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
    free(cats->arr[i].name);
  }
  free(cats->arr);
  free(cats);
}
