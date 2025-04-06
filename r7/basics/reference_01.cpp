/*

  ! Baseline:
  ! 1. There is only one difference between pointer and reference:
  !   (1). Pointers   may   point     to nothing (`NULL` or `nullptr`).
  !   (2). References never reference to nothing.

*/

#include <iostream>

void SwapByPointer(int *a, int *b) {
  int c = *a;
  *a = *b;
  *b = c;
}

void SwapByReference(int &a, int &b) {
  int c = a;
  a = b;
  b = c;
}

int main() {
  int a = 5, b = 6;

  SwapByPointer(&a, &b);
  std::cout << a << " " << b << std::endl;

  SwapByReference(a, b);
  std::cout << a << " " << b << std::endl;

  return 0;
}
