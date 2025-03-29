/*

  ! Baseline:
  ! 1. 即使有“early return”存在，RAII 也能让我们永远都不必担心资源泄漏！

*/

#include <cstdlib>
#include <iostream>

struct MemoryGuard {
  int *ptr;

  ~MemoryGuard() {
    free(ptr);
    std::cout << "Finished freeing" << std::endl;
  }
};

/// \brief Some complex task where we will allocate and free many memorys.
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
