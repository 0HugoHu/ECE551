#include "pandemic.h"

#include <stdio.h>

country_t parseLine(char * line) {
  //This function read the country,population
  //format data, and save it in a country_t struct

  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  //CODE START HERE
  //Test for empty char
  if (line == NULL) {
    fprintf(stderr, "line: Read empty line!\n");
    exit(EXIT_FAILURE);
  }

  //Read for country name
  int index = 0;
  for (; line[index] != ',' && index < MAX_NAME_LEN; index++) {
    //Do not contains a comma
    if (line[index] == '\0') {
      fprintf(stderr, "Data must be in format: country_name,population!\n");
      exit(EXIT_FAILURE);
    }
    ans.name[index] = line[index];
  }
  //Country name too long or 0 length
  if (index == MAX_NAME_LEN - 1 || index == 0) {
    fprintf(stderr, "Country name is too long or null!\n");
    exit(EXIT_FAILURE);
  }
  ans.name[index++] = '\0';

  //Read for population
  uint64_t population = 0;
  char c = 0;
  //Remove spaces after comma
  while (line[index++] == ' ' || line[index] == '\t');
  index--;

  //Flag for if whitespaces appear only after number
  int flag_white_space = 0;

  //Get value
  while ((c = line[index++]) != '\0' && c != '\n') {
    if (c >= '0' && c <= '9') {
      //Check if contains white spaces inside a number
      if (flag_white_space == 1) {
        fprintf(stderr, "Wrong population! White spaces inside a number!\n");
        exit(EXIT_FAILURE);
      }
      population = population * 10 + c - '0';
      //Overflow
      if (population > 2000000000) {
        fprintf(stderr, "Wrong population! Overflow!\n");
        exit(EXIT_FAILURE);
      }
    }
    //Contains white space after number
    else if (c == '\t' || c == ' ') {
      flag_white_space = 1;
    }
    //Number contains other ASCII char
    else {
      fprintf(stderr,
              "Population is not a number! Or the number cannot be 0 or negative!\n");
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
  //This function calculates the rolling 7-average case
  //numbers for the given n_days period.

  //CODE START HERE
  if (data == NULL) {
    fprintf(stderr, "data: No data is found!\n");
    exit(EXIT_FAILURE);
  }
  //No enough days, return succeed
  if (n_days < 7) {
    exit(EXIT_SUCCESS);
  }

  double num_avg = 0.0;
  size_t index = 0;
  //Read first 6 days data
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
      //Rolling numbers, add the current day
      num_avg += data[index];
      avg[index - 6] = num_avg / 7.0;
      //Delete the (current - 6) day data
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
  //This function calculate the cumulative sum of the country
  //per 100,000 people at the nth day.

  //CODE START HERE
  if (data == NULL) {
    fprintf(stderr, "data: No data is found!\n");
    exit(EXIT_FAILURE);
  }
  if (n_days < 0) {
    fprintf(stderr, "n_days: Days should be greater than 0!\n");
    exit(EXIT_FAILURE);
  }

  //Calculate cumulative sum per 100,000
  uint64_t num_cum = 0;
  for (int i = 0; i < n_days; i++) {
    if (data[i] >= 0) {
      num_cum += data[i];
      //First times 100,0000 avoid 0 result
      //64-bit num_cum ensures no overflow
      cum[i] = num_cum * 100000.0 / pop;
    }
    //Bad data
    else {
      fprintf(stderr, "Contains bad data!\n");
      exit(EXIT_FAILURE);
    }
  }

  //CODE END HERE
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //This function searches the maximum case number starts from
  //n_days and print the maximum number with its country name.

  //CODE START HERE
  if (countries == NULL) {
    fprintf(stderr, "country_t: No data is found!\n");
    exit(EXIT_FAILURE);
  }
  if (data == NULL) {
    fprintf(stderr, "data: No data is found!\n");
    exit(EXIT_FAILURE);
  }
  if (n_days <= 0) {
    fprintf(stderr, "n_days: Days should be greater than 0!\n");
    exit(EXIT_FAILURE);
  }

  uint64_t max = 0;
  int country_index = 0;
  //Iterate through countries
  for (size_t i = 0; i < n_countries; i++) {
    //Iterate the first n_days
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max) {
        //Find the temperate maximum number
        max = data[i][j];
        country_index = i;
      }
    }
  }

  //Print result
  printf("%s has the most daily cases with %lu\n", countries[country_index].name, max);

  //CODE END HERE
}
