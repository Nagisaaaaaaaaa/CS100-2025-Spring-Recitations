#include <exception>
#include <iostream>
#include <string>

//! In C, there are many functions returning "error code"s.
//! For example:
//! 1. `main` returns 0 if succeeded.
//! 2. `fopen` returns `NULL` if failed.
//!
//! But in C++, we use "exception"s, just like Python.
//! When functions fail, the execution is stopped, and
//! an "exception" is "thrown".
//!
//! For example, the following buggy function will throw
//! an exception called `std::invalid_argument`.
//! We have to wrap the execution with `try-catch` in order to
//! get the exception message.

/// \brief A buggy function which will throw `std::invalid_argument` when executed.
void SomeBuggyFunction() {
  int num = std::stoi("杂鱼♥～杂鱼♥～，才不会给你一个数字呢♥");
  std::cout << num << std::endl;
}

//
//
//
int main() {
  // Wrap the execution with `try-catch` in order to get the exception message.
  try {
    SomeBuggyFunction();
  } catch (const std::invalid_argument &e) {
    // These lines of codes will only be called when `std::invalid_argument`s are caught.
    const char *message = e.what();
    std::cout << "The exception message is: " << message << std::endl;
  }

  return 0;
}
