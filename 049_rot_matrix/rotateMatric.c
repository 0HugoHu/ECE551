#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Must enter a file name!\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Error with file name!\n");
    exit(EXIT_FAILURE);
  }

  char matrix[10][10] = {{'0'}};
  for (int i = 0; i < 10; i++) {
    char buffer[12] = {'0'};
    if (fgets(buffer, 12, f) == NULL) {
      fprintf(stderr, "Must have exactly 10 lines! (Result: less)\n");
      exit(EXIT_FAILURE);
    }
    if (strchr(buffer, '\n') == NULL) {
      fprintf(stderr, "Error line end!\n");
      exit(EXIT_FAILURE);
    }
    if (buffer[10] != '\n' || buffer[11] != '\0') {
      fprintf(stderr, "Must have exactly 10 elements in a line!\n");
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < 10; j++) {
      matrix[j][9 - i] = buffer[j];
    }
  }

  char buffer[11] = {'0'};
  if (fgets(buffer, 11, f) != NULL) {
    fprintf(stderr, "Must have exactly 10 lines! (Result: more)\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }

  fclose(f);

  return EXIT_SUCCESS;
}
