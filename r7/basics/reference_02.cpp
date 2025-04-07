/*

  ! Baseline:
  ! 1. There is only one difference between pointer and reference:
  !   (1). Pointers   may   point     to nothing (`NULL` or `nullptr`).
  !   (2). References never reference to nothing.

*/

#include <cstdio>

int main() {
  int a = 5;

  int *ptr = &a;
  int &ref = a;

  return 0;
}
