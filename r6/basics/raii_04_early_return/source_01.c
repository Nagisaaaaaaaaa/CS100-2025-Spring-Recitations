/*

  ! Baseline:
  ! 1. 在 C 语言编程中，我们必须非常谨慎地确保每个 `malloc` 都有一个 `free`。
  !    而如果函数的中间出现了 `return` 语句 (称之为“early return”)，
  !    这将会是雪上加霜。
  ! 2. C 语言程序员通常会在涉及资源获取、释放的地方，刻意地避免使用“early return”。

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void SomeComplexTask(bool earlyReturn) {
  int *const ptr1 = (int *)malloc(1 * sizeof(int));
  int *const ptr2 = (int *)malloc(2 * sizeof(int));
  int *const ptr3 = (int *)malloc(3 * sizeof(int));
  int *const ptr4 = (int *)malloc(4 * sizeof(int));
  int *const ptr5 = (int *)malloc(5 * sizeof(int));

  if (earlyReturn) {
    printf("Let's early return\n");

    //! WTF, too many memorys to free...
    //! It's really easy to forget something...
    free(ptr1);
    free(ptr2);
    //! Forget to free `ptr3` here, Q^Q, “丢三”。
    free(ptr4);
    free(ptr5);
    return;
  }

  //! WTF, too many memorys to free...
  //! It's really easy to forget something...
  free(ptr1);
  free(ptr2);
  free(ptr3);
  //! Forget to free `ptr4` here, T^T, “落四”。
  free(ptr5);
}

int main(void) {
  SomeComplexTask(false);
  SomeComplexTask(true);

  return 0;
}
