#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main() {
  size_t expected_answer = 1;
  int arr1[] = {1};
  if (maxSeq(arr1, 1) != expected_answer)
    return EXIT_FAILURE;
  int arr2[] = {1, 2, 4, 3};
  expected_answer = 3;
  if (maxSeq(arr2, 4) != expected_answer)
    return EXIT_FAILURE;
  int arr3[] = {1, 1, 1};
  expected_answer = 1;
  if (maxSeq(arr3, 3) != expected_answer)
    return EXIT_FAILURE;
  int arr4[] = {-1000000000, -1, 0, 1, 1000000000};
  expected_answer = 5;
  if (maxSeq(arr4, 5) != expected_answer)
    return EXIT_FAILURE;
  int arr5[] = {-1, 1, 0, 1, 0, -1};
  expected_answer = 2;
  if (maxSeq(arr5, 6) != expected_answer)
    return EXIT_FAILURE;
  int arr6[] = {1, 0};
  expected_answer = 1;
  if (maxSeq(arr6, 2) != expected_answer)
    return EXIT_FAILURE;
  int arr7[] = {};
  expected_answer = 0;
  if (maxSeq(arr7, 0) != expected_answer)
    return EXIT_FAILURE;
  int arr8[] = {-1, 0, 0, 1};
  expected_answer = 2;
  if (maxSeq(arr8, 4) != expected_answer)
    return EXIT_FAILURE;
  int arr9[] = {1, 2};
  expected_answer = 2;
  if (maxSeq(arr9, 2) != expected_answer)
    return EXIT_FAILURE;
  int arr10[] = {3, -1, 10};
  expected_answer = 1;
  if (maxSeq(arr10, 3) != expected_answer)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
