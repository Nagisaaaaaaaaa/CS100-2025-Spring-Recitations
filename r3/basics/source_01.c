/*

This piece of source code corresponds to:
Recitaion Slide 03 - Control flow.

! BASELINE:
! 1. You should be familiar with the control flow of the following structure:
!    Conditional： if-else, switch-case
!    Loops:        while-loop, for-loop, do-while
! 2. You should be able to anticipate the behavior for EACH of the given examples.
! 3. Try follow TA in recitation class and use GNU debugger for Example 2.
* BONUS:
* 4. Learn basic console GDB commands such as "break", "continue", "next", "watch", "print"...

*/

#include <stdio.h>

int main(void) {

  // Example 1: Switch case and name-lookup.
#if 0
  int i = 10;
  switch (i) {
  case 1:
    int y = 7;
  case 10:
    printf("%d\n", y);
  default:
    break;
  }
#endif

  // Example 2: Switch fall-through demonstration.
#if 0
  for (int i = 0; i < 20; ++i) {
    switch (i) {
    case 0:
      i += 5; // Where will it go?
    case 1:
      i += 2;
    case 5:
      i += 5;
    default:
      i += 4;
      break;
    }
    printf("%d\n", i);
  }
#endif

  // Example 3: For-loop and bitwise operator.
#if 0
  int i = 1024;
  for (; i; i >>= 1) {
    printf("say hi!\n");
  }
#endif

  // Example 4: When is the updation expression in for-loop executed?
#if 0
  for (int n = 9; n != 0; n--) {
    printf("n=%d\n", n--);
  }
#endif

  // Example 5: Loop corner case.
#if 0
  int c = 5;
  int n = 10000;
  do {
    n /= c;
  } while (c--);
  printf("%d\n", n);
#endif

  return 0;
}
