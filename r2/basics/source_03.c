#define __USE_MINGW_ANSI_STDIO 1 // MinGW artifacts
#include <stdio.h>

double avg(long long x, long long y) {
  return (x + y) / 2.0;
}

long double avg_pro(long long x, long long y) {
  return (x + y) / 2.0L; // Try remove the "L" suffix, see what happens
}

int main(void) {

  /*

  This piece of source code corresponds to:
  Recitaion Slide 02 - floating error.

  GCC (or any standard-compliant compiler) checks：
  if both double values have the EXACT same bit pattern in IEEE 754 representation.

  ! Baseline:
  ! 1. Understand the limited representation accuracy of floating points.
  ! 2. Be able to answer Question1.

  */

  // A double in C (typically IEEE 754 64-bit floating-point format) has:
  // - 53 bits of precision
  // A maximum representable integer without loss: 2^53 = 9007199254740992
  double m = avg(9007199254740993, 9007199254740993);
  long double n = avg_pro(9007199254740993, 9007199254740993);

  printf("%lf\n", m);
  printf("%Lf\n", n);

  double a = 0.1;
  double b = 0.2;
  double c = 0.3;

  // ! Q1: Why the following yields "a + b == c"?
  // double a = 1.0;
  // double b = 2.0;
  // double c = 3.0;

  // And so does this group
  // double a = 0.25;
  // double b = 0.5;
  // double c = 0.75;

  if (a + b == c) {
    printf("Equal\n");
  } else {
    printf("Not equal\n");
  }

  printf("a = %.20f\n", a);
  printf("b = %.20f\n", b);

  return 0;
}
