#include <stdio.h>

/*

This piece of source code corresponds to:
Recitaion Slide 01 - Historical Artifacts of C - Empty Parameter List.

You have not learned how to define your own functions.
But that's Okay. We will only use simplest examples to illustrate.

*/

// Accepts anything. Always returns 42.
int always_42() {
  return 42;
}

// Accepts nothing. Always returns 114514.
int always_114514(void) {
  return 114514;
}

int main(void) {
  // "always_42" accepts "anything", which includes a void input.
  int x = always_42();
  // Or you can give him some parameters when calling. Won't make any difference.
  int y = always_42(1, 2, 3, "dummy params");
  // "always_114514" explicity uses "void". So no parameters will be allowed when calling.
  int z = always_114514();
  // You can try give it parameters and see what happens.
  // int _ = always_114514("try any param");
  printf("x = %d\ny = %d\nz = %d\n", x, y, z);
  return 0;
}
