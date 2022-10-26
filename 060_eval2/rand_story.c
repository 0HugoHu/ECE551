#include "rand_story.h"

// ******************************************************
// All detailed function descriptions are in rand_story.h
// ******************************************************

// Random string used as the key of history category
#define UNIQUE_TAG "eHA2WXcRupyKT4dC"

// Print Error Message
void errorMessage(int errorCode, size_t extra) {
  switch (errorCode) {
    case 0:
      fprintf(stderr, "ERR: Invalid args!\nFormat: %lu args are required!", extra);
      break;
    case 1:
      fprintf(stderr, "ERR: Cannot open the file!\n");
      break;
    case 2:
      fprintf(stderr, "ERR: Cannot close the file!\n");
      break;
    case 3:
      fprintf(stderr, "ERR: No matching \"_\" at the index of %lu!\n", extra);
      break;
    case 4:
      fprintf(stderr, "ERR: Back reference should not be the start!\n");
      break;
    case 5:
      fprintf(stderr, "ERR: Back reference goes beyond boundary!\n");
      break;
    case 6:
      fprintf(stderr, "ERR: Required key does not exist!\n");
      break;
    case 7:
      fprintf(stderr, "ERR: Invalid line read! Must be in key:value format!\n");
      break;
    case 8:
      fprintf(stderr, "ERR: Key name must be at least zero character long!\n");
      break;
    case 9:
      fprintf(stderr, "ERR: Something wrong in parseLineFunc!\n");
      break;
    default:
      fprintf(stderr, "ERR: Unknown mistake!\n");
      break;
  }
  exit(EXIT_FAILURE);
}

// Check Command Line Aruguments
void checkCmdArgs(int argc, char ** argv, int argcReq, int optionalReq) {
  if (!(argc == argcReq || (argc == optionalReq && !strcmp(argv[1], "-n")))) {
    errorMessage(0, argcReq - 1);
  }
}

// Check File Open Status
FILE * checkFile(const char * filePath, const char * permission) {
  FILE * f = fopen(filePath, permission);
  if (f == NULL) {
    errorMessage(1, 0);
  }
  return f;
}

// Check File Close Status
void closeFile(FILE * f) {
  if (fclose(f) != 0) {
    errorMessage(2, 0);
  }
}

// Do Replacement for Each Line
int replacement(char * line,
                ssize_t len,
                char * flag,
                catarray_t * cats,
                catarray_t * history) {
  // Check mode: 1 - blank, 0 - random, -1 - unique
  int mode = strcmp(flag, "blank") == 0 ? 1 : (strcmp(flag, "random") == 0 ? 0 : -1);
  char * result = malloc(10 * len * sizeof(*result));

  // Length for result
  ssize_t j = 0;

  for (ssize_t i = 0; i < len; i++) {
    // If not "_", copy it to the result
    if (line[i] != '_') {
      result[j++] = line[i];
    }
    else {
      ssize_t endIndex = i + 1;
      // Find "_", read until the next "_"
      while (endIndex < len && line[endIndex] != '_') {
        endIndex++;
      }
      // No matching
      if (endIndex == len) {
        errorMessage(3, i);
      }
      // Find matching
      else {
        // MODE 1: Replace with "cat"
        if (mode == 1) {
          j = replaceMode1(result, j);
        }
        // Replace with random words
        else {
          char * content = malloc((endIndex - i) * sizeof(*content));
          strncpy(content, line + i + 1, endIndex - i - 1);
          content[endIndex - i - 1] = '\0';

          int index = containKey(cats, content);
          char * endptr;
          long number = strtol(content, &endptr, 10);

          if (index != -1) {
            // MODE 2: Unique selection
            if (mode == -1) {
              j = replaceMode2(result, j, cats, content, history);
            }
            // MODE 3: Random selection
            else {
              j = replaceMode3(result, j, cats, content, history);
            }
          }
          // MODE 4: Back reference
          else if (*endptr == '\0' && number > 0) {
            j = replaceMode4(result, j, history, number);
          }
          // Not in category
          else {
            errorMessage(6, 0);
          }
          free(content);
        }
        i = endIndex;
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

// Mode 1: Replace with "cat"
int replaceMode1(char * result, ssize_t index) {
  const char * replacement = chooseWord("blank", NULL);
  for (ssize_t k = 0; k < strlen(replacement); k++) {
    result[index++] = replacement[k];
  }
  return index;
}

// Mode 2: Replace with Unique Words
int replaceMode2(char * result,
                 ssize_t index,
                 catarray_t * cats,
                 char * content,
                 catarray_t * history) {
  const char * replacement = chooseWord(content, cats);
  for (ssize_t k = 0; k < strlen(replacement); k++) {
    result[index++] = replacement[k];
  }
  // Add it to history
  char * tag = "eHA2WXcRupyKT4dC";
  addCats(history, tag, replacement);
  // Delete it from cats
  removeCats(cats, content, replacement);
  return index;
}

// Mode 3: Replace with Random Words
int replaceMode3(char * result,
                 ssize_t index,
                 catarray_t * cats,
                 char * content,
                 catarray_t * history) {
  const char * replacement = chooseWord(content, cats);
  for (ssize_t k = 0; k < strlen(replacement); k++) {
    result[index++] = replacement[k];
  }
  char * tag = "eHA2WXcRupyKT4dC";
  addCats(history, tag, replacement);
  return index;
}

// Mode 4: Replace with Back Reference
int replaceMode4(char * result, ssize_t index, catarray_t * history, long number) {
  // If at the first a reference, rejects
  if (history->n == 0) {
    errorMessage(4, 0);
  }
  // If reference number larger than size, rejects
  if (number > history->arr[0].n_words) {
    errorMessage(5, 0);
  }
  // Replace with previous words
  const char * replacement = history->arr[0].words[history->arr[0].n_words - number];
  for (ssize_t k = 0; k < strlen(replacement); k++) {
    result[index++] = replacement[k];
  }
  char * tag = "eHA2WXcRupyKT4dC";
  addCats(history, tag, replacement);
  return index;
}

// Check If Contains a Key
int containKey(catarray_t * cats, char * key) {
  for (size_t i = 0; i < cats->n; i++) {
    if (!strcmp(key, cats->arr[i].name)) {
      return i;
    }
  }
  return -1;
}

// Check If Contains a Value
int containValue(catarray_t * cats, char * key, const char * value) {
  int index = containKey(cats, key);
  if (index == -1) {
    return -1;
  }
  for (size_t i = 0; i < cats->arr[index].n_words; i++) {
    if (!strcmp(cats->arr[index].words[i], value)) {
      return i;
    }
  }
  return -1;
}

// Read Categories from Each Line
int readCategories(char * line,
                   ssize_t len,
                   char * flag,
                   catarray_t * cats,
                   catarray_t * history) {
  char * valuePtr = strchr(line, ':');

  // If not find colon
  if (valuePtr == NULL) {
    errorMessage(7, 0);
  }

  int lenKey = valuePtr - line;
  // If key of 0 length
  if (lenKey < 0) {
    errorMessage(8, 0);
  }

  char * key = strndup(line, lenKey);
  char * value = strndup(valuePtr + 1, len - 1 - (lenKey + 1));

  // Add key-value to words list
  addCats(cats, key, value);

  free(key);
  free(value);
  free(line);
  return 1;
}

// Read Each Line From File
void readLines(FILE * f,
               parseLineFunc func,
               char * flag,
               catarray_t * cats,
               catarray_t * history) {
  char * line = NULL;
  size_t sz = 0;
  ssize_t lenRead;
  while ((lenRead = getline(&line, &sz, f)) != -1) {
    // Pass in the function pointer
    if (sz < 2 || !func(line, lenRead, flag, cats, history)) {
      errorMessage(9, 0);
    }
    line = NULL;
  }
  free(line);
}

// Add a Value to List
void addCats(catarray_t * cats, char * key, const char * value) {
  int index = containKey(cats, key);
  // Found category name and add new items
  if (index != -1) {
    cats->arr[index].words =
        realloc(cats->arr[index].words,
                (cats->arr[index].n_words + 1) * sizeof(*cats->arr[index].words));
    cats->arr[index].words[cats->arr[index].n_words] = malloc(
        (strlen(value) + 1) * sizeof(*cats->arr[index].words[cats->arr[index].n_words]));
    strncpy(cats->arr[index].words[cats->arr[index].n_words], value, strlen(value));
    cats->arr[index].words[cats->arr[index].n_words][strlen(value)] = '\0';
    cats->arr[index].n_words++;
  }
  // No category name matches, create new one
  else {
    cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
    cats->arr[cats->n].name =
        malloc((strlen(key) + 1) * sizeof(*cats->arr[cats->n].name));
    strncpy(cats->arr[cats->n].name, key, strlen(key));
    cats->arr[cats->n].name[strlen(key)] = '\0';
    cats->arr[cats->n].words = malloc(sizeof(*cats->arr[cats->n].words));
    cats->arr[cats->n].words[0] =
        malloc((strlen(value) + 1) * sizeof(*cats->arr[cats->n].words[0]));
    strncpy(cats->arr[cats->n].words[0], value, strlen(value));
    cats->arr[cats->n].words[0][strlen(value)] = '\0';
    cats->arr[cats->n].n_words = 1;
    cats->n++;
  }
}

// Remove a Value from List
void removeCats(catarray_t * cats, char * key, const char * value) {
  if (cats == NULL) {
    return;
  }
  int index = containKey(cats, key);
  int wordIndex = containValue(cats, key, value);
  if (index == -1 || wordIndex == -1 || cats->arr[index].n_words < 1) {
    errorMessage(99, 0);
  }
  int number = cats->arr[index].n_words;
  // DO NOT free it, or double free in main()
  if (number == 1 && cats->n == 1) {
    free(cats->arr[0].name);
    cats->arr[0].name = NULL;
    free(cats->arr[0].words[0]); 
    free(cats->arr[0].words);
    cats->n = 0;
  }
  // Only one word left, but >1 arrs
  else if (number == 1) {
    free(cats->arr[index].name);
    free(cats->arr[index].words[0]);
    free(cats->arr[index].words);
    cats->arr[index] = cats->arr[cats->n - 1];
    cats->n--;
  }
  // >1 words left
  else {
    free(cats->arr[index].words[wordIndex]);
    for (int i = wordIndex; i < cats->arr[index].n_words - 1; i++) {
      cats->arr[index].words[i] = cats->arr[index].words[i + 1];
    }
    cats->arr[index].n_words--;
  }
}

// Free Category
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
