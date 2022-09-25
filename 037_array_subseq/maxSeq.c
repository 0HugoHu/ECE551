#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0 || n == 1)
    return n;
  int max_num = 1;
  int cur_num = 1;
  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      cur_num++;
    }
    else {
      if (cur_num > max_num) {
        max_num = cur_num;
      }
      cur_num = 1;
    }
  }
  return cur_num > max_num ? cur_num : max_num;
}
