#include <stdio.h>

int main(void) {

  /*

  This piece of source code corresponds to:
  Recitaion Slide 02 - Integer Promotion.

  ! What does "equal" means? What does "==" actually compare?
  ! - Memory layout in binary form? --> No. (see example 3)
  ! - Numerical values? No. (see example 4)
  ! - Numerical values after integer promotion + implicit arithmetic conversion? Yes.

  Integer Promotion:
  Before comparing, small integer types like char and short are promoted to int
  (if they can fit inside int) — otherwise, they become unsigned int.

  The complete arithmetic conversions can become very tricky! --> Check cppreference
  https://en.cppreference.com/w/c/language/conversion
  The integer promotion promises to:
  preserve the value, including the sign. (see example 3)

  ! BASELINE:
  ! 1. You should understand basic definition of integer promotion( and when it happens).
  ! 2. You should understand why example 1 & 2 behaves as shown.
  ! 3. You should learn that signed-unsigned comparisons in C can be DANGEROUS.
  * BONUS:
  * 4. You should understand why example 3 & 4 behaves differently.

  */

  // Example 1:
  char a = 42;
  unsigned char b = a;

  if (a == b /* What does the "==" actually compare here? */) {
    printf("a and b are the same !!\n");
  } else {
    printf("a and b are NOT the same !!\n");
  }
  // Explain 1:
  // a (char) gets promoted to int: 42 -> (int) 42
  // b (unsigned char) gets promoted to int: 42 -> (int) 42
  // Since both are now the same type and value, a == b is true.

  // Example 2:
  char c = -42;
  unsigned char d = c;
  // Now it seems that d is "positive" and c is "negative".
  // Are they still equal?

  if (c == d) {
    printf("c and d are the same !!\n");
  } else {
    printf("c and d are NOT the same !!\n");
  }
  // Explain 2:
  // c (char) gets promoted to int: -42 -> (int) -42
  // d (unsigned char) gets promoted to int: 214 (due to unsigned wrapping)
  // Now we compare -42 with 214, so c != d.

  // Example 3:
  char e = -1;           // 1111 1111 Binary
  unsigned char f = 255; // 2^8 - 1, 1111 1111 Binary

  if (e == f) {
    printf("e and f are the same !!\n");
  } else {
    printf("e and f are NOT the same !!\n");
  }
  // ! Key takeaway:
  // ! Even if the binary representations match, the values being compared are different.

  // Example 4: (Assuming 32-bit unsigned int)
  int g = -1;                  // "1111 ... 1111" Binary
  unsigned int h = 4294967295; // 2^32 - 1, "1111 ... 1111" Binary
  printf("g = %d, h = %u\n", g, h);
  if (g == h) {
    printf("g and h are the same !!\n");
  } else {
    printf("g and h are NOT the same !!\n");
  }
  // Explain 4: g is -1 (signed), h is 4294967295 (unsigned)
  // Before comparison, g is promoted to unsigned int: (unsigned int)-1 -> 4294967295
  // Now we compare 4294967295 == 4294967295, which is true!

  return 0;
}
