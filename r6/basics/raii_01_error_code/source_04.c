/*

  ! Baseline:
  ! 1. C 语言程序员通常会通过“返回 0 或者其他数字”，来表示某个函数是否“有在好好工作”。
  ! 2. 我们称这种“错误处理方式”为“error code”，返回值中的 0、`EXIT_FAILURE` 等数字就是一个个“code”。
  ! 3. 如何实现一个遵循“error code”的函数？请看 `SomeComplexTask` 的实现。
  ! 4. 如何调用一个遵循“error code”的函数？请看 `main` 中的调用。

*/

#include <stdio.h>
#include <stdlib.h>

int SomeComplexTask(void) {
  FILE *file = fopen("Try to open a non-existent file.txt", "r");
  if (file == NULL) {
    printf("Failed to open the file\n");
    return EXIT_FAILURE;
  }

  int errCode = fclose(file);
  if (errCode != 0) {
    printf("Failed to close the file\n");
    return EXIT_FAILURE;
  }

  int *arr = malloc(sizeof(int) * 0xFFFFFFFFFFFFFFFLLU);
  if (arr == NULL) {
    printf("Failed to allocate the memory\n");
    return EXIT_FAILURE;
  }

  return 0;
}

int main(void) {
  int errCode = SomeComplexTask();
  if (errCode != 0) {
    printf("Failed to finish the complex task\n");
    return EXIT_FAILURE;
  }

  return 0;
}
