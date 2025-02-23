/// \file
/// \brief This file shows that, C++ codes are prone to memory leaks
/// because of the exceptions.

//
//
//
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

/// \brief A buggy function which will throw `std::invalid_argument` when executed.
void SomeBuggyFunction() {
  int num = std::stoi("杂鱼♥～杂鱼♥～，才不会给你一个数字呢♥");
  std::cout << num << std::endl;
}

//
//
//
int main() {
  try {
    int *const ptr = (int *)malloc(10 * sizeof(int));

    // An exception will be thrown here.
    SomeBuggyFunction();

    //! These lines will not be called because of the exception.
    printf("This `printf` will not be executed\n");
    //! Memory leak!
    free(ptr);
  } catch (const std::invalid_argument &e) {
    const char *message = e.what();
    std::cout << "The exception message is: " << message << std::endl;
  }

  return 0;
}
