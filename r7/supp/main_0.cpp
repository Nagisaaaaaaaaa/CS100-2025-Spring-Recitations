/// \file
/// \brief This file shows the non-zero-argument constructions with `()` and `{}`.
/// Their main differences:
/// `{}` can be used for:
///   (1). C-style structures (aggregate initialization).
///   (2). C++ constructors, with narrow conversions banned.
/// `()` can be used for:
///   (1). C++ constructors, with narrow conversions allowed.

//
//
//
struct A {
  int v;
};

class B {
public:
  B(int v) : v_(v) {}

private:
  int v_;
};

int main() {
  {
    int v0(10);
    int v1{10};
  }

  {
    int v0(10.0);
    // int v1{10.0}; //! Narrowing conversion from `double` to `int`.
  }

  {
    // A v0(10); //! No matching function for call to `A::A(int)`.
    A v1{10}; //! Aggregate initialization.
  }

  {
    // A v0(10.0); //! No matching function for call to `A::A(double)`.
    // A v1{10.0}; //! Narrowing conversion from `double` to `int`.
  }

  {
    B v0(10); //! Calls the one-argument constructor.
    B v1{10}; //! Calls the one-argument constructor.
  }

  {
    B v0(10.0); //! Calls the one-argument constructor.
    // B v1{10.0}; //! Narrowing conversion from `double` to `int`.
  }

  return 0;
}
