#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main() {
  int arr1[] = {1};
  if (maxSeq(arr1, 1) != 1)
    return EXIT_FAILURE;
  int arr2[] = {1, 2, 4, 3};
  if (maxSeq(arr2, 4) != 3)
    return EXIT_FAILURE;
  int arr3[] = {1, 1, 1};
  if (maxSeq(arr3, 3) != 1)
    return EXIT_FAILURE;
  int arr4[] = {-1000000000, -1, 0, 1, 1000000000};
  if (maxSeq(arr4, 5) != 5)
    return EXIT_FAILURE;
  int arr5[] = {-1, -1, 0, 1, 2, 3};
  if (maxSeq(arr5, 6) != 5)
    return EXIT_FAILURE;
  int arr6[] = {1, 0};
  if (maxSeq(arr6, 0) != 0)
    return EXIT_FAILURE;
  int arr7[] = {1, 2, 3, 4, 4};
  if (maxSeq(arr7, 5) != 4)
    return EXIT_FAILURE;
  int arr8[] = {-1, 0, 0, 1};
  if (maxSeq(arr8, 4) != 2)
    return EXIT_FAILURE;
  int arr9[] = {-1, -2, -3, -4};
  if (maxSeq(arr9, 4) != 1)
    return EXIT_FAILURE;
  int arr10[] = {15, 13, 11, 1};
  if (maxSeq(arr10, 4) != 1)
    return EXIT_FAILURE;
  int arr11[] = {1, 3, 5, 7, 2, 4, 6};
  if (maxSeq(arr11, 7) != 4)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
