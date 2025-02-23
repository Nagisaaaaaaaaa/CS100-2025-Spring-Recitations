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

//
//
//
void DoSomething(bool earlyReturn) {
  MemoryGuard guard1{(int *)malloc(1 * sizeof(int))};
  MemoryGuard guard2{(int *)malloc(2 * sizeof(int))};
  MemoryGuard guard3{(int *)malloc(3 * sizeof(int))};
  MemoryGuard guard4{(int *)malloc(4 * sizeof(int))};
  MemoryGuard guard5{(int *)malloc(5 * sizeof(int))};

  if (earlyReturn) {
    printf("Let's early return");
    return;
  }
}

int main() {
  DoSomething(false);
  DoSomething(true);

  return 0;
}
