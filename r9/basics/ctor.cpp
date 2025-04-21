#include <cstddef>
#include <iostream>

struct Data {
  Data(size_t s) { std::cout << "Default CTOR @ " << this << "\n"; }

  Data(const Data &) { std::cout << "Copy    CTOR @ " << this << "\n"; }

  Data(Data &&) { std::cout << "Move    CTOR @ " << this << "\n"; }

  size_t s;
  int *b;
};

const Data getData(size_t s) {
  return {s}; // Modern alternative to `return Data(s)`
}

void SeparateLine() {
  std::cout << "----------------------------" << "\n";
}

int main() {
  // Try `g++ -std=c++14 -fno-elide-constructors ctor.cpp`
  // Disable copy-elision optimization
  //! Copy-elision becomes mandatory since C++17 ~
  auto v3 = getData(42);
  SeparateLine();

  auto v4 = std::move(getData(42));
  SeparateLine();

  return 0;
}
