#include <iostream>

// 继承与构造

int just42() {
  static int count = 0;
  ++count;
  std::cout << "Count of " << __func__ << " has been called: " << count << "\n";
  return 42;
}

#include <iostream>

class Base {
public:
  Base()
      : base_protected_member_(just42())
      , base_private_member_(just42()) {
    base_private_member_ = just42();
    std::cout << "I'm at Base Constructor body!\n";
  }

protected:
  int base_protected_member_ = just42();

private:
  int base_private_member_ = just42();
};

class Derived : public Base {
public:
  Derived()
      : derived_private_member_(just42()) {
    std::cout << "I'm at Derived Constructor body!\n";
  }

private:
  int derived_private_member_;
};

int main() {
  //   Base b;    // just42会被调用几次？
  Derived d; // just42会被调用几次？
  return 0;
}

//* Order of Constructor Calls:
//* 1. Memory Allocation: Space for the derived object is allocated.
//* 2. Base Class Constructor: The base constructor is called to initialize the base part of the object.
//* 3. Non-static data members of the derived class are initialized in the order of their declaration.
//* 4. Derived Constructor Body: Finally, the body of the derived class constructor is executed.
