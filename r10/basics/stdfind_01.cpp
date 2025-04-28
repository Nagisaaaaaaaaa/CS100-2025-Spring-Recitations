/*

  ! Baseline:
  ! 1. Learn basic use of std::find, std::find_if， std::find_if_not

*/

#include <algorithm>
#include <array>
#include <iostream>

//* This piece of code is provided at:
//* https://en.cppreference.com/w/cpp/algorithm/find

bool is_even(int i) {
  return i % 2 == 0;
}

void example_contains() {
  const std::array haystack{1, 2, 3, 4};

  for (const int needle : {3, 5})
    if (std::find(haystack.begin(), haystack.end(), needle) == haystack.end())
      std::cout << "haystack does not contain " << needle << '\n';
    else
      std::cout << "haystack contains " << needle << '\n';
}

void example_predicate() {
  for (const auto &haystack : {std::array{3, 1, 4}, {1, 3, 5}}) {
    const auto it = std::find_if(haystack.begin(), haystack.end(), is_even);
    if (it != haystack.end())
      std::cout << "haystack contains an even number " << *it << '\n';
    else
      std::cout << "haystack does not contain even numbers\n";
  }
}

int main() {
  example_contains();
  example_predicate();
}
