/// \file
/// \brief This file creates an image based on the PPM image format, which
/// is almost the simplest image format in the world.
/// See https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/theppmimageformat
/// for a detailed introduction.
///
/// As you will see, we can `printf` strings into another file.
/// That is how we create the image.

//
//
//
#include <stdio.h>

int main(void) {
  // The P3 means colors are in ASCII.
  printf("P3\n");

  // Then 3 columns and 2 rows.
  printf("3 2\n");

  // Then 255 for max color.
  printf("255\n");

  // Then RGB triplets.
  printf("255   0   0\n      0 255   0\n      0   0 255\n");
  printf("255 255   0\n    255 255 255\n      0   0   0\n");

  return 0;
}
