/*

  This piece of source code corresponds to:
  Recitaion Slide 04 - Dynamic Memory Management.

  ! Baseline:
  ! 1. What are the 2 ways to write a 2D array.
  ! 2. Always use the second one.

*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int nX = 50, nY = 60;

#if 0
  int **arr = malloc(sizeof(int *) * nY);
  for (int y = 0; y < nY; ++y)
    arr[y] = malloc(sizeof(int) * nX);

  for (int y = 0; y < nY; ++y)
    for (int x = 0; x < nX; ++x) {
      // arr[y][x] = ...;
    }

  for (int y = 0; y < nY; ++y)
    free(arr[y]);
  free(arr);
#else
  int *arr = malloc(sizeof(int) * nX * nY);

  for (int y = 0; y < nY; ++y)
    for (int x = 0; x < nX; ++x) {
      // arr[x + y * nX] = ...;
    }

  free(arr);
#endif

  return 0;
}
