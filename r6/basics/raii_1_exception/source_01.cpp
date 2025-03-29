/*

  ! Baseline:
  ! 1. 所谓的“错误处理方式”，除了“error code”之外，还有一种叫做“exception”。
  ! 2. error code v.s. exception:
  !   2.1. error code: 错误发生时，返回非 0 值。
  !   2.2. exception : 错误发生时，一拳给程序打个半死。
  ! 3. C 使用 error code ，而 C++ 和 Python 使用 exception。

*/

#include <cstdio>
#include <vector>

int main() {
  printf("Start allocating\n");

  std::vector<int> v(0xFFFFFFFFFFFFFFFLLU);

  printf("Finished allocating\n");

  return 0;
}
