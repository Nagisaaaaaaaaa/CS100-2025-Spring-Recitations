/*

  ! Baseline:
  ! 1. RAII 能帮助我们自动处理“manual frees”和“early returns”。
  ! 2. 即使对于那些不存在异常的编程语言，RAII 同样非常重要。

*/

#include <cstdlib>
#include <iostream>

struct MemoryGuard {
  int *const ptr;

  ~MemoryGuard() {
    free(ptr);
    std::cout << "Finished freeing" << std::endl;
  }
};

void SomeComplexTask(bool earlyReturn) {
  MemoryGuard guard1{(int *)malloc(1 * sizeof(int))};
  MemoryGuard guard2{(int *)malloc(2 * sizeof(int))};
  MemoryGuard guard3{(int *)malloc(3 * sizeof(int))};
  MemoryGuard guard4{(int *)malloc(4 * sizeof(int))};
  MemoryGuard guard5{(int *)malloc(5 * sizeof(int))};
  int *const ptr1 = guard1.ptr;
  int *const ptr2 = guard2.ptr;
  int *const ptr3 = guard3.ptr;
  int *const ptr4 = guard4.ptr;
  int *const ptr5 = guard5.ptr;

  if (earlyReturn) {
    printf("Let's early return\n");

    //! No longer need to worry about early returns.
    return;
  }

  //! No longer need to worry about manual frees.
}

int main() {
  SomeComplexTask(false);
  SomeComplexTask(true);

  return 0;
}
