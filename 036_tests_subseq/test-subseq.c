#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main() {
  int arr1[] = {1};
  if (maxSeq(arr1, 1) != 1)
    return EXIT_FAILURE;
  int arr2[] = {1, 2, 4, 3};
  if (maxSeq(arr2, 4) != 2)
    return EXIT_FAILURE;
  int arr3[] = {1, 1, 1};
  if (maxSeq(arr3, 3) != 1)
    return EXIT_FAILURE;
  int arr4[] = {-1000000000, -1, 0, 1, 1000000000};
  if (maxSeq(arr4, 5) != 5)
    return EXIT_FAILURE;
  int arr5[] = {-1, 1, 0, 1, 0, -1};
  if (maxSeq(arr5, 6) != 2)
    return EXIT_FAILURE;
  int arr6[] = {1, 0};
  if (maxSeq(arr6, 2) != 1)
    return EXIT_FAILURE;
  int arr7[] = {};
  if (maxSeq(arr7, 0) != 0)
    return EXIT_FAILURE;
  int arr8[] = {-1, 0, 0, 1};
  if (maxSeq(arr8, 4) != 2)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
