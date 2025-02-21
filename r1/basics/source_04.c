#include <stdio.h>

/*

This piece of source code corresponds to:
Recitaion Slide 01 - Examples of "printf" and undefined behavior.

*/

int main(void) {

  double e_doub = 2.718281828;

  char e_char = 'e';

  int e_int = e_doub;

  // Print "e_doub" as an integer?
  // Maybe you expect that "%d" will smartly do the conversion for you?
  printf("%d\n", e_doub);
  // Something more crazy?
  printf("%d\n", e_char);

  // Print "int_e" as an integer
  printf("%d\n", e_int);

  // Recommended practices of printing floats
  printf("%lf\n", e_doub);   // print as long float
  printf("%e\n", e_doub);    // decimal exponent notation
  printf("%.3lf\n", e_doub); // round to 1e-3

  return 0;
}
