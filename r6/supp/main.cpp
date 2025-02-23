#include <cstdlib>
#include <iostream>

/// \brief A memory guard automatically frees the OWNing memory when
/// the instance is out of scope.
struct MemoryGuard {
  // We use `nullptr` instead of `NULL` in C++ codes.
  int *const ptr = nullptr;

  // Just like python, C++ allows us to define methods (member functions) of a `struct`.
  // The following method, `~MemoryGuard`, is a special method called "destructor".
  // Destructors will ALWAYS be called when the instance is out of scope.
  ~MemoryGuard() {
    free(ptr);
    printf("Memory has been freed");
  }
};

//
//
//
int main() {
  // Instantiate a memory guard with a dynamic array of 10 `int`s.
  // The memory is now OWNed by `guard`.
  MemoryGuard guard{(int *)malloc(10 * sizeof(int))};

  // Get a non-OWNing pointer of the dynamic array.
  // "Non-OWNing" means that we should not call `free` on it.
  int *const ptr = guard.ptr;

  for (int i = 0; i < 10; ++i)
    ptr[i] = i;

  return 0;
}
