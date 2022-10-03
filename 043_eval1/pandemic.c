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
  //CODE START HERE
  if (data == NULL) {
    fprintf(stderr, "No data is found!\n");
    exit(EXIT_FAILURE);
  }

  double num_avg = 0.0;
  size_t index = 0;
  //Read first 6 data
  for (; index < 6; index++) {
    if (data[index] >= 0) {
      num_avg += data[index];
    }
    //No sufficient data
    else {
      fprintf(stderr, "At least 7 data is required!\n");
      exit(EXIT_FAILURE);
    }
  }

  //Calculate rolling average
  for (; index < n_days; index++) {
    if (data[index] >= 0) {
      num_avg += data[index];
      avg[index - 6] = num_avg / 7.0;
      num_avg -= data[index - 6];
    }
    //Bad data
    else {
      fprintf(stderr, "Contains bad data!\n");
      exit(EXIT_FAILURE);
    }
  }
  //CODE END HERE
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
