/// \file
/// \brief This file shows that, C/C++ codes are prone to memory leaks
/// because of the early returns.

//
//
//
#include <cstdlib>
#include <iostream>

/// \brief Some complex function where we will allocate and free many memorys.
void SomeComplexFunction(bool earlyReturn) {
  int *const ptr1 = (int *)malloc(1 * sizeof(int));
  int *const ptr2 = (int *)malloc(2 * sizeof(int));
  int *const ptr3 = (int *)malloc(3 * sizeof(int));
  int *const ptr4 = (int *)malloc(4 * sizeof(int));
  int *const ptr5 = (int *)malloc(5 * sizeof(int));

  if (earlyReturn) {
    printf("Let's early return");

    //! WTF, too many memorys to free...
    //! It's really easy to forget something...
    free(ptr1);
    free(ptr2);
    free(ptr4);
    free(ptr5);
    return;
  }

  free(ptr1);
  free(ptr2);
  free(ptr3);
  free(ptr4);
  free(ptr5);
}

//
//
//
int main() {
  SomeComplexFunction(false);
  SomeComplexFunction(true);

  return 0;
}
