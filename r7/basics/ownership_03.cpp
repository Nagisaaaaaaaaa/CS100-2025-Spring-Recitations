/*

  ! Baseline:
  ! 1. Who owns the array in this example?
  ! 2. Why? 谁负责 RAII，谁就拥有 ownership (所有权)！

*/

#include <stdlib.h>

struct Vector {
  int *data;

  ~Vector() { free(data); }
};

int main() {
  //! `vec` owns the array.
  Vector vec{(int *)malloc(sizeof(int) * 5)};

  //! `data` does not own the array.
  int *data = vec.data;

  return 0;
}
