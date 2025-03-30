/*

  This piece of source code corresponds to:
  Recitaion 06 - Struct.

  ! Baseline:
  ! 1. Learn how to use struct to package a bunch of input / output variables.
  ! 2. Get familiar with the provided examples.

*/

#include <stdbool.h>
#include <stdio.h>

// Toy example: Interval
typedef struct {
  float left;
  float right;
} Interval;

// Navie implementation, correct but messy.
bool contain(float x, float min, float max) {
  return (min <= x) && (x <= max);
}

// Better version. Different floats are separated.
bool contain_pro(float x, Interval intv) {
  return (intv.left <= x) && (x <= intv.right);
}

// Suppose you want a function to return a triangle in 3D.
// How would you like to implement it?

// Attempt 1:
float get_tri_a_x() {

  // ... some complicated computation
  float a_x = 0.0F; // compute coordinate
  return a_x;
}

// However, you need the following as well:
// float get_tri_a_y() {}
// float get_tri_a_z() {}
// float get_tri_b_x() {}
// float get_tri_b_y() {}
// float get_tri_b_z() {}
// float get_tri_c_x() {}
// float get_tri_c_y() {}
// float get_tri_c_z() {}

// Attempt 2:
// clang-format off
void get_tri_vertices(
    float *a_x, float *a_y, float *a_z, 
    float *b_x, float *b_y, float *b_z, 
    float *c_x, float *c_y, float *c_z) {

    // ... some complicated computation
    *a_x = 0.0F;
    *a_y = 1.0F;
    *a_z = -1.0F;
    // .. Similar things for the other vertices
}

// clang-format on

// Attempt 3: struct wrapping
typedef struct Vertex3D {
  float px;
  float py;
  float pz;
} v3;

typedef struct Triangle3D {
  v3 A;
  v3 B;
  v3 C;
} tri3;

// clang-format off
tri3 get_tri() {
  // ... some complicated computation

  v3 A = (v3){0, 0, 0};
  v3 B = (v3){0, 1, 0};
  v3 C = (v3){1, 0, 0};

  return (tri3){A, B, C};
}

// clang-format on

// Suppose we want to describe an air-conditioner with C code,
// whoese status (temperature, on/off, wind-direction) can change.
// You can avoid the use of scattered variables by defining a struct.

enum AC_wind_dir { Upward, Downward, Mid, Loop };

typedef struct AirConditioner {
  float temperature;
  bool turned_on;
  enum AC_wind_dir wind_dir;

} AC;

void remote_controller(AC *ptrAC /* ... maybe more user input */) {
  ptrAC->temperature = 25.0F; // adjust temperature..
  ptrAC->turned_on = true;    // turn on
  ptrAC->wind_dir = Loop;     // loop wind
}

int main(void) {

  return 0;
}
