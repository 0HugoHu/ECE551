#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int findMaxFreq(FILE * f);

int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("Must have 1 input file name!");
    printf("Must have 1 intput file name!");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("File does not exist!");
    perror("File does not exist!");
    exit(EXIT_FAILURE);
  }

  int key = findMaxFreq(f);

  fclose(f);

  printf("%d\n", key);

  return EXIT_SUCCESS;
}

int findMaxFreq(FILE * f) {
  int hashtable[26] = {0};
  int ch = 0;
  int max = 0;
  int index = -1;
  while ((ch = fgetc(f)) != EOF) {
    if (isalpha(ch)) {
      ch = tolower(ch);
      hashtable[ch - 'a']++;
      if (hashtable[ch - 'a'] > max) {
        max = hashtable[ch - 'a'];
        index = ch - 'a';
      }
    }
  }
  for (int i = 0; i < 26; i++) {
    if (hashtable[i] == max && i != index) {
      printf("No maximum frequency!");
      perror("No maximum frequency!");
      exit(EXIT_FAILURE);
    }
  }

  return (index + 26 - 4) % 26;
}
