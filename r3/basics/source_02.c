/*

This piece of source code corresponds to:
Recitaion Slide 03 - Pointers and arrays.

! BASELINE:
! 1. You should be familiar with the control flow of the following structure:
!    Conditional： if-else, switch-case
!    Loops:        while-loop, for-loop, do-while
! 2. You should be able to anticipate the behavior for EACH of the given examples.
! 3. Try follow TA in recitation class and use GNU debugger for Example 2.
* BONUS:
* 4. Learn basic console GDB commands such as "break", "continue", "next", "watch", "print"...

*/

#include <stdio.h>

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

  // ! An array is NOT a pointer.
  // ! A pointer is NOT an array.
  // ! What bridges the two concepts is the fact that:
  // ! Array can be implicity converted to a pointer (to its first element).

#if 1
  a_ptr = arr;            // What happens here? a_ptr <- {int * (&arr[0]) <= int[100] (arr)}
  int res = *(a_ptr + 3); // Pointer arithmetic, covered in class.
  printf("%d\n", res);
#endif

// Try Casting between pointer types
#if 1
  float b = 3.14F;
  float *b_ptr = &b;
  a_ptr = b_ptr; // Force a_ptr points to where a float exists
  printf("%d\n", *a_ptr);
#endif

  return 0;
}
