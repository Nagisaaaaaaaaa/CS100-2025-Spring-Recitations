/*

  This piece of source code corresponds to:
  Lecture 09 - `struct`.

  ! Baseline:
  ! 1. Why `typedef` is helpful for defining `struct`s.
  ! 2. How to implement a `Vec`.

*/

#include <stdbool.h>
#include <stdio.h>

/// \brief A 2D vector which contains only `int`s.
typedef struct {
  int x, y;
} Vec;

bool Eq(Vec a, Vec b) {
  return a.x == b.x && a.y == b.y;
}

bool Neq(Vec a, Vec b) {
  return !Eq(a, b);
}

Vec Neg(Vec v) {
  return (Vec){-v.x, -v.y};
}

Vec Add(Vec a, Vec b) {
  return (Vec){a.x + b.x, a.y + b.y};
}

Vec Sub(Vec a, Vec b) {
  return Add(a, Neg(b));
}

Vec Mul(Vec a, int b) {
  return (Vec){a.x * b, a.y * b};
}

int main(void) {
  Vec a = {0, 1};
  Vec b = {2, 4};

  Vec c = Add(a, b);
  printf("%d %d\n", c.x, c.y);

  return 0;
}
