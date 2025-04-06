/*

  ! Baseline:
  ! 1. Please review the RAII part of `r6/basics`, T^T...
  ! 2. How to implement a `Vector` with RAII.

*/

#include <iostream>

struct Vector {
  int *data;

  ~Vector() { free(data); }
};

int main() {
  Vector vec{(int *)malloc(sizeof(int) * 10)};

  return 0;
}
