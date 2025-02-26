/// \file
/// \brief This file shows when there are zero argument,
/// things will become much more weird!
/// Terrible design!

//
//
//
#include <type_traits>

struct A {
  int v;
};

struct B {
  int v;

  B() {}
};

int main() {
  {
    int i0;   // Default initialization, the integer is uninitialized.
    int i1(); // Type of `i1` is even not `int`, it is actually a function.
    int i2{}; // Value initialization, the integer is zero-initialized as `0`.

    static_assert(std::is_same_v<decltype(i0), int>);
    static_assert(!std::is_same_v<decltype(i1), int>);
    static_assert(std::is_same_v<decltype(i2), int>);
  }

  {
    int *p0;   // Default initialization, the pointer is uninitialized.
    int *p1(); // Type of `p1` is even not `int`, it is actually a function.
    int *p2{}; // Value initialization, the pointer is zero-initialized as `nullptr`.

    static_assert(std::is_same_v<decltype(p0), int *>);
    static_assert(!std::is_same_v<decltype(p1), int *>);
    static_assert(std::is_same_v<decltype(p2), int *>);
  }

  {
    A a0;   // Default initialization, the struct is uninitialized.
    A a1(); // Type of `a1` is even not `int`, it is actually a function.
    A a2{}; // Aggregate initialization, `a2.v` is value-initialized (zero-initialized) as `0`.

    static_assert(std::is_same_v<decltype(a0), A>);
    static_assert(!std::is_same_v<decltype(a1), A>);
    static_assert(std::is_same_v<decltype(a2), A>);
  }

  {
    B b0;   // Calls the zero-argument constructor.
    B b1(); // Type of `b1` is even not `int`, it is actually a function.
    B b2{}; // Calls the zero-argument constructor.

    static_assert(std::is_same_v<decltype(b0), B>);
    static_assert(!std::is_same_v<decltype(b1), B>);
    static_assert(std::is_same_v<decltype(b2), B>);
  }

  return 0;
}
