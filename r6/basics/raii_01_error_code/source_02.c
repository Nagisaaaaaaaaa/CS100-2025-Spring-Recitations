/*

  ! Baseline:
  ! 1. C 语言通过特定的返回值来告诉我们，某个函数是否“有在好好工作”。
  !   1.1. `fopen` 通过返回 NULL 来告诉我们文件无法打开。
  !   1.2. `fclose` 通过返回 0 来告诉我们文件被正常关闭。

*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
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
