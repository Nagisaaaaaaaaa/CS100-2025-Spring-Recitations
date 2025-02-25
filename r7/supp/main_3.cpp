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
  }

  // For vector of `bool`s.
  {
    std::vector<bool> vec{true};
    auto v = vec[0];
    static_assert(!std::is_same_v<decltype(v), bool>);
    std::cout << typeid(v).name() << std::endl;
    std::cout << v << std::endl;
    vec[0] = false;
    std::cout << v << std::endl;
  }
}
