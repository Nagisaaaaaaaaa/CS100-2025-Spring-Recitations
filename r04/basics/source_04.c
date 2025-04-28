/*

  This piece of source code corresponds to:
  Recitaion Slide 04 - Arrays.

  ! Baseline:
  ! 1. ALWAYS use `Func(int *arr)`, NEVER use `Func(int arr[])`, even though they are the same.

*/

#include <stdio.h>
#include <stdlib.h>

void Func(int *arr) {
  // Do something here.
}

int main(void) {
  int arr0[10];
  int *arr1 = malloc(sizeof(int) * 10);

  int *ptr = arr0; // Then, you can use `ptr` as if you are using `arr0`.

  Func(arr0);
  Func(arr1);

  free(arr1);

  return 0;
}
