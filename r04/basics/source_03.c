/*

  This piece of source code corresponds to:
  Recitaion Slide 04 - Arrays.

  ! Baseline:
  ! 1. `sizeof(arr0)` is different from `sizeof(arr1)`.

*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int arr0[10];
  int *arr1 = malloc(sizeof(int) * 10);

  printf("%d\n", (int)sizeof(arr0));
  printf("%d\n", (int)sizeof(arr1));

  free(arr1);

  return 0;
}
