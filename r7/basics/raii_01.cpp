/*

  ! Baseline:
  ! 1. Please review the four RAII parts of `r6/basics`, T^T...
  ! 2. How to implement `Vector` with RAII.
  ! 3. Why `size_t` is used here instead of `int` or `unsigned int`?

*/

#include <cstdio>
#include <cstdlib>

struct Vector {
  int *data;

  ~Vector() { free(data); }
};

int main() {
  Vector vec{(int *)malloc(sizeof(int) * 5)};

  for (size_t i = 0; i < 5; ++i)
    vec.data[i] = i;

  for (size_t i = 0; i < 5; ++i)
    printf("%d\n", vec.data[i]);

  return 0;
}
