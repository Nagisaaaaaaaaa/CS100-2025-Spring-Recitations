/// \file
/// \brief This file introduces how to use `MemoryGuard` to
/// automatically free the memory without explicitly calling `free`.

//
//
//
#include <cstdlib>
#include <iostream>

/// \brief A memory guard automatically frees the OWNing memory when
/// the instance is out of scope.
struct MemoryGuard {
  // We use `nullptr` instead of `NULL` in C++ codes.
  int *ptr = nullptr;

  // Just like python, C++ allows us to define methods (member functions) of a `struct`.
  // The following method, `~MemoryGuard`, is a special method called "destructor".
  // Destructors will ALWAYS be called when the instance is out of scope.
  ~MemoryGuard() {
    free(ptr);
    ptr = nullptr;
    printf("Memory has been freed\n");
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

  // We can manipulate the dynamic array with the non-OWNing pointer.
  for (int i = 0; i < 10; ++i) {
    ptr[i] = i;
    std::cout << ptr[i] << std::endl;
  }

  // When `main` returns, the destructor of `guard`, `~MemoryGuard`, will
  // be automatically called, which means that
  // the memory will be automatically freed.
  return 0;

  //! This technique is called RAII (Resource Acquisition Is Initialization).
  //! Recall that `guard` OWNs the dynamic array during initialization.
  //! In this example, memory is the resource.
  //! RAII is almost the most important programming technique for C++!
}
