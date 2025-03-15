/*

  This piece of source code corresponds to:
  Recitaion Slide 04 - C Strings Library.

  ! Baseline:
  ! 1. `strlen` means string length.
  ! 2. All C strings are terminated with '\0', called null-terminated.

*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  const char *str = "Hello World!";

  printf("%d\n", (int)strlen(str));

  for (int i = 0; i < strlen(str); ++i)
    printf("%c", str[i]);
  printf("\n");

  assert(str[strlen(str)] == '\0');

  return 0;
}
