#include "pandemic.h"

#include <stdio.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  //CODE START HERE
  //Test for empty char
  if (line == NULL) {
    fprintf(stderr, "Read empty line!\n");
    exit(EXIT_FAILURE);
  }

  //Read for country name
  int index = 0;
  for (; line[index] != ',' && index < 256; index++) {
    //Do not contains a comma
    if (line[index] == '\0') {
      fprintf(stderr, "Data must be in format: country_name,population!\n");
      exit(EXIT_FAILURE);
    }
    ans.name[index] = line[index];
  }
  ans.name[index++] = '\0';

  //Read for population
  uint64_t population = 0;
  char c = 0;
  while ((c = line[index++]) != '\0' && c != '\n') {
    if (c >= '0' && c <= '9') {
      population = population * 10 + c - '0';
    }
    //Number contains other ASCII char
    else {
      fprintf(stderr, "Population is not a number!\n");
      exit(EXIT_FAILURE);
    }
  }

  //Population is not over write
  if (population <= 0) {
    fprintf(stderr, "Population is wrong!\n");
    exit(EXIT_FAILURE);
  }
  ans.population = population;
  //CODE END HERE

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
