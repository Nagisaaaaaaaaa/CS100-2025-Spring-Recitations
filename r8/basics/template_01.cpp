/*

  ! Baseline:
  ! 1. Always use `new` and `delete` instead of `malloc` and `free`.

*/

#include <iostream>

struct Vector {
  int *data;

  ~Vector() { delete[] data; }
};

int main() {
  Vector vec{new int[5]};

  for (size_t i = 0; i < 5; ++i)
    vec.data[i] = i;

  for (size_t i = 0; i < 5; ++i)
    std::cout << vec.data[i] << std::endl;

  return 0;
}
