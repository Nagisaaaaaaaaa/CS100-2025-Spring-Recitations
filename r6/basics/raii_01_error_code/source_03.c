/*

  ! Baseline:
  ! 1. C 语言通过特定的返回值来告诉我们，某个函数是否“有在好好工作”。
  !   1.1. `fopen` ...
  !   1.2. `fclose` ...
  !   1.3. `malloc` 通过返回 NULL 来告诉我们内存分配失败。

*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int *arr = malloc(sizeof(int) * 0xFFFFFFFFFFFFFFFLLU);
  if (arr == NULL) {
    printf("Failed to allocate the memory\n");
    return EXIT_FAILURE;
  }

  free(arr);

  return 0;
}
