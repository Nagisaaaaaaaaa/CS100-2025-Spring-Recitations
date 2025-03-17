/*

  This piece of source code corresponds to:
  Recitaion Slide 04 - C Strings Library.

  ! Baseline:
  ! 1. All C strings are terminated with '\0', called null-terminated.
  ! 2. The usages of `strlen` and `strcpy`.
  ! 3. Never forget the `+ 1` in `malloc(sizeof(char) * (strlen(str) + 1))`.

*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  const char *str = "Hello World!";

  printf("%d\n", (int)strlen(str));

  for (int i = 0; i < strlen(str); ++i)
    printf("%c", str[i]);
  printf("\n");

  assert(str[strlen(str)] == '\0');

  char buffer0[100];
  strcpy(buffer0, str);
  printf("%s\n", buffer0);

  char *buffer1 = malloc(sizeof(char) * (strlen(str) + 1));
  strcpy(buffer1, str);
  printf("%s\n", buffer1);
  free(buffer1);

  return 0;
}
