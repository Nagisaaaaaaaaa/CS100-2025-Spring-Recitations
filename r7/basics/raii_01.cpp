/*

  ! Baseline:
  ! 1. Please review the RAII part of `r6/basics`, T^T...
  ! 2. How to implement a `Vector` with RAII.

*/

#include <iostream>

struct Vector {
  int *const data;

  ~Vector() { free(data); }
};

int main() {
  Vector v{(int *)malloc(sizeof(int) * 10)};

  return 0;
}
