/*

  ! Baseline:
  ! 1. 如何实现多个遵循“error code”的函数？
  !    请看 `SomeComplexFileTask` 和 `SomeComplexTask` 的实现。

*/

#include <stdio.h>
#include <stdlib.h>

int SomeComplexFileTask(void) {
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

  return 0;
}

int SomeComplexTask(void) {
  int errCode = SomeComplexFileTask();
  if (errCode != 0) {
    printf("Failed to finish the complex file task\n");
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
