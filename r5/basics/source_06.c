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
