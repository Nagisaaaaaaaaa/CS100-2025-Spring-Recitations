/*

  This piece of source code corresponds to:
  Recitation Slide 05 - File I/O.

  ! Baseline:
  ! 1. Write to an opened file with `fputc`, `fputs`, etc.

*/

#include <stdio.h>

int main() {
  FILE *fileIn = fopen(__FILE__, "r");
  FILE *fileOut = fopen("source_temp.c", "w");

  // Copy all characters of `fileIn` into `fileOut`.
  char ch;
  while ((ch = fgetc(fileIn)) != EOF)
    fputc(ch, fileOut);

  //! Never forget to close the files.
  fclose(fileIn);
  fclose(fileOut);

  return 0;
}
