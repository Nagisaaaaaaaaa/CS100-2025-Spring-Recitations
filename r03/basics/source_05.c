#include <assert.h>
#include <math.h>
#include <stdio.h>

int main() {
  /*

    This piece of source code corresponds to:
    Homework 1 - Quadratic equation.

    * BONUS:
    * 1. How to hack OJ testcases with runtime errors?

  */

  // -x^2 + 2x = 0
  int a = -1, b = 2, c = 0;

  int delta = b * b - 4 * a * c;
  double x1 = (-(double)b - sqrt((double)delta)) / (double)(2 * a);
  double x2 = (-(double)b + sqrt((double)delta)) / (double)(2 * a);

  //! This line of code will change `WA` to `RTE` on OJ, which
  //! means that we can hack OJ testcases with runtime errors!
  assert(x1 < x2);

  printf("x1 = %.3lf, x2 = %.3lf\n", x1, x2);

  return 0;
}
