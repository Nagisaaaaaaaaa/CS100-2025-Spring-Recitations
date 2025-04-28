/*

  This piece of source code corresponds to:
  Recitaion Slide 04 - Malloc review and "const".

  ! Baseline:
  ! 1. Remember malloc using principles.
  ! 2. Understand the behavior of "const" when modifying a variable.
  * Bonus:
  * 3. Understand the limitation of "const" and why we are still using it.

*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void printArray(const int *arr, size_t len) {
  //   int *ptr = &arr[0];
  for (size_t i = 0; i < len; i++) {
    printf("%d\n", arr[i]);
    // Suppose a naughty elf adds this line into your code
    // ++arr[i]; // allowed?
    // ++ptr[i]; // allowed if we "cheat gcc"? What about g++?
  }
}

int main(void) {

  // Example 1:
  // Tips of using malloc()
#if 1
  int *p = malloc(sizeof(float));
  *p = 1089;
  printf("%d\n", *p);
  free(p);
#endif

  // Example 2:
  // First encounter with "const"
#if 0
  const int b;
  int *const c;
  const int *const d; // What is d?
  int *const e[10];   // What is e?
#endif

  // Example 3:
  // "const" usage in function parameter passing
#if 0
  int a[] = {1, 2, 3, 4, 5};
  printArray(a, 5);
#endif

  return 0;
}
