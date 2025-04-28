/*

  This piece of source code corresponds to:
  Recitaion 06 - Struct.

  ! Baseline:
  ! 1. Get familiar with examples below.

*/

#include <float.h>
#include <stdbool.h>
#include <stdio.h>

// Suppose you want a function to return a triangle in 3D.
// How would you like to implement it?

float some_computation(void) {
  return 42.0F;
}

// Attempt 1:
double get_tri_a_x() {

  // ... some complicated computation
  double a_x = some_computation(); // compute coordinate
  return a_x;
}

// However, you need the following as well:
// double get_tri_a_y() {}
// double get_tri_a_z() {}
// double get_tri_b_x() {}
// double get_tri_b_y() {}
// double get_tri_b_z() {}
// double get_tri_c_x() {}
// double get_tri_c_y() {}
// double get_tri_c_z() {}

// Attempt 2:
// clang-format off
void get_tri_vertices(
    double *a_x, double *a_y, double *a_z, 
    double *b_x, double *b_y, double *b_z, 
    double *c_x, double *c_y, double *c_z) {

    // ... some complicated computation
    *a_x = some_computation();
    *a_y = some_computation();
    *a_z = some_computation();
    // .. Similar things for the other vertices
}

// clang-format on

// Attempt 3: struct wrapping
typedef struct Vertex3D {
  double px;
  double py;
  double pz;
} v3;

void print_v3(v3 vertex) {
  printf("(%.3F, %.3F, %.3F)\n", vertex.px, vertex.py, vertex.pz);
}

typedef struct Triangle3D {
  v3 A;
  v3 B;
  v3 C;
} tri3;

void print_tri3(tri3 triangle) {
  printf("A: ");
  print_v3(triangle.A);
  printf("B: ");
  print_v3(triangle.B);
  printf("C: ");
  print_v3(triangle.C);
}

// clang-format off
tri3 get_tri() {
  // ... some complicated computation

  v3 A = (v3){0, 0, 0};
  v3 B = (v3){0, 1, 0};
  v3 C = (v3){1, 0, 0};

  return (tri3){A, B, C};
}

// clang-format on

int main(void) {

  tri3 ABC = get_tri();
  print_tri3(ABC);

  return 0;
}
