#include <stdio.h>

// ------------ Some helper functions ---------------

int Alice_student_ID(void) {
  printf("I'm Alice. My student ID is 42.\n");
  return 42;
}

int Bob_student_ID(void) {
  printf("I'm Bob. My student ID is 10086.\n");
  return 10086;
}

int Charlie_student_ID(void) {
  printf("I'm Charlie. My student ID is 114514.\n");
  return 114514;
}

int Alice_write(int *p) {
  *p = 42;
  return 1;
}

int Bob_write(int *p) {
  *p = 10086;
  return 1;
}

int Charlie_write(int *p) {
  *p = 114514;
  return 1;
}

int add_three(int a, int b, int c) {
  return a + b + c;
}

// ------------ Some helper functions ---------------

int main(void) {

  /*

  This piece of source code corresponds to:
  Recitaion Slide 02 - evaluation order.

  Unspecified behavior (Safety guaranteed; Correctness NOT guaranteed)
  The compiler is free to evaluate function arguments in any order,
  but the program remains well-defined.

  Undefined behavior (Safety NOT guaranteed; Correctness NOT guaranteed)
  The program has no predictable outcome due to violating rules in the C standard
  (such as modifying the same variable multiple times without sequence points).

  ! Baseline:
  ! 1. Understand the difference between Undefined behavior v.s. Unspecified behavior.
  ! 2. Be able to list some examples of undefined / unspecified behaviors.
  ! 3. Unspecified order + Cross interference --> Undefined behavior.
  ! 3. Fully understand the evalutaion order of [&& || ?: ,].

  */

  // Unspecified behavior:

  // In what order they are called?
  // Do a quick survey in class!
  int _ = add_three(Alice_student_ID(), Bob_student_ID(), Charlie_student_ID());
  printf("Different compilers may evaluate arguments in different orders!\n");

  // Undefined behavior:
  int N = 0;
  _ = add_three(Alice_write(&N), Bob_write(&N), Charlie_write(&N));
  printf("N = %d\n", N);

  // Comma operator:
  // (e1, e2) --> e1 evaluated and discared.
  int a = 1;
  int b = (a++, a + 100, a - 10);
  printf("b = %d\n", b);

  return 0;
}
