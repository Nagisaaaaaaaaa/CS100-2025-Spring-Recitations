/*

  This piece of source code corresponds to:
  Recitaion 05 - Quiz Review.

  A further demo for variable lifetime.

*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int *staticAddress() {
  static int a = 42;
  return &a;
}

int *localAddress() {
  int a = 42;
  return &a;
  // You are allowed to return the address.
  // After all, it's just an address and nothing special.
}

int main(void) {

  int *add1 = staticAddress();
  int *add2 = localAddress();

  printf("add1: %p\n", add1);
  printf("add2: %p\n", add2); // It's okay.

  printf("*add1: %d\n", *add1);
  printf("*add2: %d\n", *add2); // Danger zone!

  return 0;
}
