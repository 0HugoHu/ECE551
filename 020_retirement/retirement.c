#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int currentAge = startAge;
  for (; currentAge < startAge + working.months; currentAge++) {
    printf(
        "Age %3d month %2d you have $%.2lf\n", currentAge / 12, currentAge % 12, initial);
    initial += working.contribution + initial * working.rate_of_return;
  }

  for (; currentAge < startAge + working.months + retired.months; currentAge++) {
    printf(
        "Age %3d month %2d you have $%.2lf\n", currentAge / 12, currentAge % 12, initial);
    initial += retired.contribution + initial * retired.rate_of_return;
  }
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);

  return 0;
}
