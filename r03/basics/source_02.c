/*

  This piece of source code corresponds to:
  Recitaion Slide 03 - Pointers and arrays.

  ! BASELINE:
  ! 1. You should be able to answer the 9 questions on the recitation slide.
  ! 2. You should FULLY undertstand Takeaway #1.
  ! 3. You should FULLY remember Takeaway #2 and be able to:
  !    independently answer Lec.06-p33 and r.03-p40, and
  !    independently determine some complicated nested type.
  ! 4. Understand how arrays are passed in function parameters.
  ! 5. Bear in mind that what you learn today is just theoritical.
  !    It helps you grow profound understanding of pointers and arrays.
  !    But it is BY NO MEANS the encouraged code style.

*/

#include <stdio.h>

void testFunc(int *arr[30][10]) {
  printf("@testFunc: Param accepted !\n");
}

int main(void) {
  // Define an array, holding 100 integers
  int arr[100] = {42, 114514, 6657, 10086, 2025};

  // Define an integer, and a pointer points to it
  int a = 42;
  int *a_ptr = &a;

  // Check the size of int[100] (arr) and int* (a_ptr)
#if 1
  printf("The size of int[100] is %d Bytes.\n", (int)sizeof(arr));
  printf("The size of int *    is %d Bytes.\n", (int)sizeof(a_ptr));
#endif

  // ! Takeaway #1:
  // ! An array is NOT a pointer.
  // ! A pointer is NOT an array.
  // ! What bridges the two concepts is the fact that:
  // ! Array can be implicity converted to a pointer (to its first element).
  // ! Suppose T is a type. T[N] => T* (the type of &T[0]).

#if 0
  a_ptr = arr;            // What happens here? a_ptr <- {int * (&arr[0]) <= int[100] (arr)}
  int res = *(a_ptr + 3); // Pointer arithmetic, covered in class.
  printf("%d\n", res);
#endif

// Try Casting between pointer types
#if 0
  float b = 3.14F;
  float *b_ptr = &b;
  a_ptr = b_ptr; // Force a_ptr points to where a float is stored
  printf("%d\n", *a_ptr);
#endif

  // What are these horrible-looking types?
  int *(*ugly_var)[10];
  int *(**very_ugly_var[10])[42];
  // How do we interpret them?
  // ! Takeaway #2:
  // ! Major principles for interpreting nested types:
  // ! |----- 1. From inside (near the variable name) to outside.
  // ! |----- 2. Combine precedence: " [ ] " > " * ", if no "( )" forces.
  // ! |----- 3. Try both top-down and down-top interpretation.
  // ! |----- 4. You are required to learn this, but not encouraged to write any code like this.

#if 1
  // Try some function call with array-type params.
  int *(*arr_1)[10] = {};
  testFunc(arr_1);

#endif

  return 0;
}
