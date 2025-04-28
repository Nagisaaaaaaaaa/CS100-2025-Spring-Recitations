/*

  This piece of source code corresponds to:
  Recitation Slide 03 - Preprocessor Directives.

  ! BASELINE:
  ! 1. Understand `#include <...>` and `#include "..."`.
  ! 2. Understand `#define` and `#undef`.
  ! 3. Understand why `MAX` is usually dangerous.
  ! 4. Understand why header guards are necessary.

*/

// Use `<...>` for standard library headers.
#include <stdio.h>

// Use `"..."` for user-defined headers.
#include "include_03.h"
#include "include_03.h" // Why including twice is still safe ?

// Object-like macros.
#define mian main
#define O    0
#define QAQ  printf("QAQ\n")

// Function-like macros.
#define MAX(a, b)  ((a) < (b) ? (b) : (a)) //* Good!
#define MAX1(a, b) a < b ? b : a           //! Bad!
#define MAX2(a, b) (a < b ? b : a)         //! Bad!

int mian() {
#if 1
  int v = MAX(5, 6);
  printf("%d\n", v);
  QAQ;
#endif

#if 1
  // Why `MAX1` is bad?
  int v1 = MAX1(5, 6) + 1;
  printf("%d\n", v1);
#endif

#if 1
  // Why `MAX2` is bad?
  int v2 = MAX2(5 & 1, 6 & 1); // 5 & 1 == 1, 6 & 1 == 0.
  printf("%d\n", v2);
#endif

#if 1
  // `MAX` is good, but...
  int v3 = MAX(5, ++v);
  printf("%d %d\n", v, v3);
#endif

  return O;
}

// Undefine these bad macros.
#undef mian
#undef O
#undef QAQ

#undef MAX1
#undef MAX2
