/*

  This piece of source code corresponds to:
  Recitaion 06 - Struct.

  ! Baseline:
  ! 1. Understand what union basically does.
  ! 2. Understand the following examples.

*/

#include <stdint.h>
#include <stdio.h>

// Question: How to peek the bits in a float?

typedef uint32_t u32;

union FloatInt {
  float f;
  unsigned int i;
};

// Interpret as unsigned int to allow for bitwise operations.
void printBinary(u32 num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1U);
    if (i % 4 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}

int main() {
  union FloatInt data;
  data.f = 3.14F;

  printf("Float: %f\n", data.f);
  printf("IEEE 754 Representation: ");
  printBinary(data.i);

  return 0;
}
