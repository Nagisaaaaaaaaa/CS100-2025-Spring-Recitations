/*

  ! Baseline:
  ! 1. 如何通过使用 `MY_EXPECT` 这个宏，来让“error code”用起来更方便？
  ! 2. “Error code”这种“错误处理方式”的优点：
  !   2.1. 显式地要求所有人都必须检查函数返回值，绝对严谨、绝对安全。
  !   2.2. 一旦发生错误，`MY_EXPECT` 会自动打印出整个栈 (调用顺序)，能让我们一眼看到错误是在哪里发生的。
  ! 3. “Error code”这种“错误处理方式”的缺点：
  !   3.1. 检查“error code”写代码难受，不检查“error code” debug 难受，横竖都难受。

  * Bonus:
  * 4. 为什么 `MY_EXPECT` 的实现里面会有一个 `do-while` 循环呢？
  * 5. 通过阅读 `r5/supp`，来学习如何实现更强大的 `MY_EXPECT`。
  * 6. 和 C 一样，Rust 也是一门使用“error code”来进行“错误处理”的编程语言，
  *    但它是怎么做到让写代码不那么难受的呢？

*/

#include <stdio.h>
#include <stdlib.h>

#define MY_EXPECT(cond, explanation)                                                                                   \
  do {                                                                                                                 \
    if (!(cond)) {                                                                                                     \
      fprintf(stderr, "Expectation (%s) failed at [%s:%d] (" explanation ")\n", #cond, __FILE__, __LINE__);            \
      return EXIT_FAILURE;                                                                                             \
    }                                                                                                                  \
  } while (0)

int SomeComplexFileTask(void) {
  FILE *file = fopen("Try to open a non-existent file.txt", "r");
  MY_EXPECT(file != NULL, "Failed to open the file");

  int errCode = fclose(file);
  MY_EXPECT(errCode == 0, "Failed to close the file");

  return 0;
}

int SomeComplexTask(void) {
  int errCode = SomeComplexFileTask();
  MY_EXPECT(errCode == 0, "Failed to finish the complex file task");

  int *arr = malloc(sizeof(int) * 0xFFFFFFFFFFFFFFFLLU);
  MY_EXPECT(arr != NULL, "Failed to allocate the memory");

  return 0;
}

int main(void) {
  int errCode = SomeComplexTask();
  MY_EXPECT(errCode == 0, "Failed to finish the complex task");

  return 0;
}
