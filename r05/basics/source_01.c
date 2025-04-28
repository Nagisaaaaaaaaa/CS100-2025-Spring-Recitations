/*

  This piece of source code corresponds to:
  Recitaion 05 - Quiz review.

  ! Baseline:
  ! 1. Understand the name look-up strategy.
  ! 2. Understand the variable name shadowing.
  * Bonus (but very important):
  * 3. Develop some knowledge of variable lifetime. (See the table below)

  Variable lifetime in different memory areas:

                      BEGIN               END
  - Stack             into scope          out of scope
  - Heap              malloc / new        free / delete
  - Static Storage    program begins      program terminates

*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// (global) arr is a pointer in "static storage".
// Its lifetime begins when the program starts,
// and does not die until the program terminates.
int *arr; // 静态存储区

void alloc_arr(int n) {
  // With the call of calloc, we allocate n * sizeof(int) Bytes
  // on the "heap". Now the global arr points to the corresponding
  // location on the heap.
  arr = calloc(n, sizeof(int)); // 堆
}

void free_arr(void) {
  // Free the heap memory where the global arr points to.
  free(arr); // 释放堆内存
}

int main(void) {

  alloc_arr(20);

  // Local arr is declared, thus shadowing the global arr.
  // However, the global arr still holds its place in static storage.
  // It's just that we can't visit it with the name 'arr'.
  // The local arr is stored on "stack".
  int arr[2] = {1, 2}; // 栈

  free_arr(); // It's all about global arr. No UB is triggered.

  printf("%d\n", arr[0]); // Visit the local arr.

  return 0;
}
