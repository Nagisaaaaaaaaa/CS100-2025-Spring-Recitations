/*

  This piece of source code corresponds to:
  Recitaion 06 - Struct.

  ! Baseline:
  ! 1. Get familiar with the examples below.

*/

#include <float.h>
#include <stdbool.h>
#include <stdio.h>

bool eq(double x, double y) {
  double diff = x > y ? (x - y) : (y - x);
  return diff < 1e-8;
}

typedef struct {
  double k; // slope
  double b; // intercept
} Line2d;

void print_line(Line2d l) {
  printf("Line: y = %.3f * x + %.3f\n", l.k, l.b);
}

enum pattern { parallel, intersect, overlap };

// What is the advantage of this struct?
typedef struct {
  enum pattern has_hit;
  double hit_x;
  double hit_y;
} HitRecord;

void print_hitrec(HitRecord rec) {
  switch (rec.has_hit) {
  case parallel:
    printf("Lines are parallel!\n");
    break;
  case overlap:
    printf("Lines overlap!\n");
    break;
  case intersect:
    printf("Lines intersect at (%.3f, %.3f)!\n", rec.hit_x, rec.hit_y);
    break;
  }
}

HitRecord check_intersect(Line2d l1, Line2d l2) {
  if (eq(l1.k, l2.k)) {
    // overlap
    if (eq(l1.b, l2.b)) {
      return (HitRecord){overlap, 0.0, 0.0};
    }
    // parallel
    return (HitRecord){parallel, 0.0, 0.0};
  }
  // intersect
  double x = (l1.b - l2.b) / (l2.k - l1.k);
  double y = (l1.k * x) + l1.b;
  return (HitRecord){intersect, x, y};
}

int main(void) {
  Line2d l1 = {.k = 1.0, .b = 0.0};
  Line2d l2 = {.k = 0.0, .b = 1.0};
  print_line(l1);
  print_line(l2);
  print_hitrec(check_intersect(l1, l2));

  return 0;
}
