/*

  This piece of source code corresponds to:
  Recitaion Slide 04 - Arrays.

  ! Baseline:
  ! 1. What is Variable-Length Arrays (VLA)?
  ! 2. NEVER use VLA, use `malloc` and `free` instead.

*/

#include <stdio.h>

int main(void) {
  int n;
  scanf("%d", &n); // Try a large number, such as 1000000.
  int arr[n];

  printf("OwO\n");

  return 0;
}
