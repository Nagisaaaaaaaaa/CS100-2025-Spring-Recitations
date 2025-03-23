/*

  This piece of source code corresponds to:
  Recitation Slide 05 - Function Pointers.

  ! Baseline:
  ! 1. How to use a function pointer to dynamically choose the function to call.

*/

#include <stdio.h>

int Squared(int v) {
  return v * v;
}

int Negative(int v) {
  return -v;
}

int main(void) {
  int (*func)(int);

  func = Squared;
  for (int i = 0; i < 5; ++i) {
    int res = func(i);
    printf("%d\n", res);
  }

  func = Negative;
  for (int i = 0; i < 5; ++i) {
    int res = func(i);
    printf("%d\n", res);
  }

  return 0;
}
