#include <iostream>

struct Type {
  Type() = default;

  Type(const Type &) { printf("0\n"); }

  Type &operator=(const Type &) {
    printf("1\n");
    return *this;
  }

  Type(Type &&) { printf("2\n"); }

  Type &operator=(Type &&) {
    printf("3\n");
    return *this;
  }
};

void Func(const Type &type) {}

int main() {
  Func(Type{});

  return 0;
}
