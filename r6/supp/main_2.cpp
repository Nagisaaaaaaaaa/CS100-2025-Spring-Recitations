#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

/// \brief A buggy function which will throw `std::invalid_argument` when executed.
void SomeBuggyFunction() {
  int num = std::stoi("杂鱼♥～杂鱼♥～，才不会给你一个数字呢♥");
  std::cout << num << std::endl;
}

/// \brief A memory guard automatically frees the OWNing memory when
/// the instance is out of scope.
struct MemoryGuard {
  int *const ptr = nullptr;

  ~MemoryGuard() {
    free(ptr);
    printf("Memory has been freed\n");
  }
};

//
//
//
int main() {
  try {
    MemoryGuard guard{(int *)malloc(10 * sizeof(int))};
    int *const ptr = guard.ptr;

    for (int i = 0; i < 10; ++i) {
      ptr[i] = i;
      std::cout << ptr[i] << std::endl;
    }

    SomeBuggyFunction();
  } catch (const std::invalid_argument &e) {
    const char *message = e.what();
    std::cout << "The exception message is: " << message << std::endl;
  }

  return 0;
}
