/*

  ! Baseline:
  ! 1. Please review the four RAII parts of `r6/basics`, T^T...
  ! 2. How to implement a `Vector` with RAII.

*/

#include <iostream>

struct Vector {
  int *data;

  ~Vector() { free(data); }
};

int main() {
  Vector vec{(int *)malloc(sizeof(int) * 5)};

  for (size_t i = 0; i < 5; ++i)
    vec.data[i] = i;

  for (size_t i = 0; i < 5; ++i)
    std::cout << vec.data[i] << std::endl;

  return 0;
}
