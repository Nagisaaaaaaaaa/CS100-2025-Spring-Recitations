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

    for (int i = 0; i < 10; ++i) {
      ptr[i] = i;
      std::cout << ptr[i] << std::endl;
    }

    SomeBuggyFunction();

    //! These lines will not be called because of the exception.
    //! Memory leak!
    printf("This `printf` will not be executed\n");
    free(ptr);
  } catch (const std::invalid_argument &e) {
    const char *message = e.what();
    std::cout << "The exception message is: " << message << std::endl;
  }

  return 0;
}
