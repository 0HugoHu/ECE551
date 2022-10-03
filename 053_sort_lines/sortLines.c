#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sort_stdin(void * f) {
  char ** lines = NULL;
  lines = malloc(sizeof(*lines));
  char * cur_line = NULL;
  cur_line = malloc(sizeof(char *));
  int num_line = 0;
  size_t sz = 0;
  while (getline(&cur_line, &sz, f) >= 0) {
    lines = realloc(lines, (num_line + 1) * sizeof(*lines));
    lines[num_line++] = cur_line;
    cur_line = NULL;
  }

  sortData(lines, num_line);

  for (int i = 0; i < num_line; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }

  free(cur_line);
  free(lines);
}

void sort_lines(int argc, char ** argv) {
  for (int i = 0; i < argc - 1; i++) {
    FILE * f = fopen(argv[i + 1], "r");
    if (f == NULL) {
      fprintf(stderr, "Cannot open some of the files!\n");
      exit(EXIT_FAILURE);
    }

    sort_stdin(f);

    if (fclose(f) != 0) {
      fprintf(stderr, "Cannot close some of the files!\n");
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    sort_stdin(stdin);
  }
  else if (argc > 1) {
    sort_lines(argc, argv);
  }
  else {
    fprintf(stderr, "Error argument number!");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
