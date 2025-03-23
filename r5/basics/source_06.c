/*

  This piece of source code corresponds to:
  Recitation Slide 05 - File I/O.

  ! Baseline:
  ! 1. Open or close a file with `fopen` or `fclose`.
  ! 2. The `r` means opening the file for reading. You should also know `w`, `a`, `r+`, etc.
  ! 3. Read an opened file with `fgetc`, `fgets`, etc.

*/

#include <stdio.h>

int main(void) {
  // You can even "open yourself".
  FILE *fileIn = fopen(__FILE__, "r");

  // Print all characters of the file, until end of file (EOF).
  char ch;
  while ((ch = fgetc(fileIn)) != EOF)
    putchar(ch);

  //! Never forget to close the file.
  fclose(fileIn);

  return 0;
}
