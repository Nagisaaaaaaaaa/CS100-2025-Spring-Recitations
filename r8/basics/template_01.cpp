/*

  ! Baseline:
  ! 1. Always use `new` and `delete` instead of `malloc` and `free`.

*/

#include <iostream>

struct Vector {
  int *data;

  ~Vector() { delete[] data; } // 从今天开始，我们不再用 free，而是用 delete 和 delete[]。
};

int main() {
  Vector vec{new int[5]}; // 从今天开始，我们不再用 malloc，而是用 new 和 new[]。

  for (size_t i = 0; i < 5; ++i)
    vec.data[i] = i;

  for (size_t i = 0; i < 5; ++i)
    std::cout << vec.data[i] << std::endl;

  return 0;
}
