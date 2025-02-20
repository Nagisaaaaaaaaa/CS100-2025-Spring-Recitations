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
