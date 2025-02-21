#include <stdio.h>

/*

This piece of source code corresponds to:
Recitaion Slide 01 - An example: the "A + B" problem.

*/

int main(void) {
  int A, B;
  char C;

  // Correct Implementation 1
  scanf("%d%d", &A, &B);
  // Try follwing input:
  // "1" + "0" + "SPACE" + "2" + "ENTER"
  // "1" + "0" + "ENTER" + "2" + "ENTER"
  // "1" + "0" + "-" + "2" + "ENTER"
  // "1" + "0" + "-" + "a" + "ENTER"

  // Correct Implemantation 2
  // scanf("%d\n%d", &A, &B);

  // Correct Implemantation 3
  // scanf("%d %d", &A, &B);

  // Incorrect Implemantation 1
  // scanf("%d\n%d\n", &A, &B);

  // Why omitting white space is OK?
  // Try below:
  // scanf("%d", &A);
  // scanf("%d", &B);

  printf("A = %d\nB = %d\nA + B = %d\n", A, B, A + B);

  // Read cppreference.com:
  // Most conversion specifiers first consume all consecutive whitespace.
  // Exeptions exist, such as "%c".
  // Try:
  // scanf("%c", &C);
  // printf("C = %c\n", C);

  return 0;
}
