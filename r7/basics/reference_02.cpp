/*

  ! Baseline:
  ! 1. There is only one difference between pointer and reference:
  !   (1). Pointers   may   point     to nothing (`NULL` or `nullptr`).
  !   (2). References never reference to nothing.

*/

int main() {
  int a = 5;

  int *ptr = &a;
  int &ref = a;

  const int *ptr = &a;
  const int &ref = a;

  return 0;
}
