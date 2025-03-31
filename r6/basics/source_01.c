/*

  This piece of source code corresponds to:
  Recitaion 06 - Struct.

  ! Baseline:
  ! 1. Get familiar with examples below.

*/

#include <float.h>
#include <stdbool.h>
#include <stdio.h>

// Navie implementation, correct but messy.
bool contain_(double x, double min, double max) {
  return (min <= x) && (x <= max);
}

typedef struct {
  double left;
  double right;
} Interval;

// Better version. Different floats are separated.
bool contain(double x, Interval intv) {
  return (intv.left <= x) && (x <= intv.right);
}

//clang-format off
double clamp(double x, Interval intv) {
  if (x > intv.right)
    return intv.right;
  if (x < intv.left)
    return intv.left;
  return x;
}

double span(Interval intv) {
  double res = intv.right - intv.left;
  return (res > 0 ? res : 0);
}

void print_intv(Interval intv) {
  printf("(%e, %e); span = %e\n", intv.left, intv.right, span(intv));
}

// maximum span of double representation
const Interval universe = {.left = -DBL_MAX, .right = +DBL_MAX};

// maximum span of double representation
const Interval empty = {.left = +DBL_MAX, .right = -DBL_MAX};

// Suppose you want a function to return a triangle in 3D.
// How would you like to implement it?

int main(void) {
  Interval A = {10.0, 42.0};
  print_intv(A);
  print_intv(universe);
  print_intv(empty);

  return 0;
}
