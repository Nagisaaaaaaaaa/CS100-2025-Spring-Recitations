/// \file
/// \brief This file shows how RAII (`MemoryGuard`) helps
/// prevent memory leaks caused by the early returns.

//
//
//
#include <cstdlib>
#include <iostream>

/// \brief A memory guard automatically frees the OWNing memory when
/// the instance is out of scope.
struct MemoryGuard {
  int *ptr = nullptr;

  ~MemoryGuard() {
    free(ptr);
    ptr = nullptr;
    printf("Memory has been freed\n");
  }
};

/// \brief Some complex function where we will allocate and free many memorys.
void SomeComplexFunction(bool earlyReturn) {
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

    //! We no longer need to worry about early returns.
    return;
  }
}

//
//
//
int main() {
  SomeComplexFunction(false);
  SomeComplexFunction(true);

  return 0;
}
