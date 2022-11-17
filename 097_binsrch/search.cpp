#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
    if (low > high) {
        exit(EXIT_FAILURE);
    }
    if (low == high) {
        return high;
    }
    if (f->invoke(high - 1) <= 0) {
        return high - 1;
    }
    int guess = 0, mid = 0;
    high -= 1;
    while (low <= high) {
        mid = (low + high) / 2;
        guess = f->invoke(mid);
        if (guess == 0) return mid;
        if (guess > 0) high = mid - 1;
        else low = mid + 1;
    }
    if (guess > 0) return mid - 1;
    return mid;
}