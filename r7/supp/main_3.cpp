/// \file
/// \brief This file shows one of the most notorious STL design:
/// `std::vector<bool>`.
/// See https://en.cppreference.com/w/cpp/container/vector_bool.
/// Crazy-terrible design!

//
//
//
#include <iostream>
#include <vector>

int main() {
  // For vector of `int`s.
  {
    std::vector<int> vec{233};
    auto v = vec[0];
    static_assert(std::is_same_v<decltype(v), int>);
    std::cout << typeid(v).name() << std::endl;
    std::cout << v << std::endl;
    vec[0] = 466;
    std::cout << v << std::endl;

    for (auto &v : vec)
      v = 233;
    std::cout << vec[0] << std::endl;
  }

  // For vector of `bool`s.
  {
    std::vector<bool> vec{true};
    auto v = vec[0];
    static_assert(!std::is_same_v<decltype(v), bool>);
    std::cout << typeid(v).name() << std::endl;
    std::cout << v << std::endl;
    vec[0] = false;
    //! The value has been changed!
    std::cout << v << std::endl;

    //! Even unable to compile the following `for`-loop!
    //! Cannot bind non-const lvalue reference of type ... to an rvalue of type ...
    // for (auto &v : vec)
    //   v = true;

    //! Have to use `auto v` instead of `auto &v` here!
    for (auto v : vec)
      v = true;
    std::cout << vec[0] << std::endl;
  }
}
