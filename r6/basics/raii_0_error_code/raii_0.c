/*

  ! Baseline:
  ! 1. 这短短两行代码有哪些危险的地方？

*/

#include <stdio.h>

int main(void) {
  FILE *file = fopen("Try to open a non-existent file.txt", "r");

  fclose(file);

  return 0;
}
