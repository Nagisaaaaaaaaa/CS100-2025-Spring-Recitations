/// \file
/// \brief This file shows `()` and `{}` may
/// have very different behaviors for exactly the same class.
/// Terrible design!

//
//
//
#include <array>
#include <string>
#include <vector>

int main() {
  {
    std::vector<int> v0(10); //! [0, 0, 0, 0, 0, 0, 0, 0, 0, 0].
    std::vector<int> v1{10}; //! [10], list-initialization, different from `std::array`!
    // std::vector<int> v2{10.0}; //! Narrowing conversion from `double` to `int`.
  }

  {
    // std::array<int, 3> v0(0, 1, 2); //! No matching function for call to `std::array<int, 3>::array(int, int, int)`.
    std::array<int, 3> v1{0, 1, 2}; //! [0, 1, 2], aggregate-initialization, different from `std::vector`!
    // std::array<int, 3> v2{0.0, 1.0, 2.0}; //! Narrowing conversion from `double` to `int`.
  }

  {
    // They are the same.
    std::string v0("QAQ");
    std::string v1{"QAQ"};
  }

  return 0;
}
