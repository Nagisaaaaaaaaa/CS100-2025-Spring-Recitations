/*

  ! Baseline:
  ! 1. C++ `struct` and `class` are almost the same.
  !   (1). `struct` members are public  by-default.
  !   (2). `class`  members are private by-default.
  ! 2. Constructors.
  !   (1). How to implement constructors for C++ classes.
  !   (2). What is the "default" constructor and why called "default"?
  ! 3. Member functions.
  !   (1). How to implement member functions for C++ classes.
  !   (2). Difference between `const` and non-`const` member functions.

  * Bonus:
  * 4. It is better for all `struct` member variables to be public .
  * 5. It is better for all `class`  member variables to be private.

*/

#include <iostream>

class Vector {
public:
  Vector() = default;

  Vector(size_t size) : data_((int *)malloc(sizeof(int) * size)), size_(size) {
    for (size_t i = 0; i < size_; ++i)
      data_[i] = 0;
  }

  ~Vector() { free(data_); }

public:
  int *data() { return data_; }

  const int *data() const { return data_; }

  size_t size() const { return size_; }

private:
  int *data_ = nullptr;
  size_t size_ = 0;
};

int main() {
  Vector vec(5);

  for (size_t i = 0; i < vec.size(); ++i)
    vec.data()[i] = i;

  for (size_t i = 0; i < vec.size(); ++i)
    std::cout << vec.data()[i] << std::endl;

  Vector vec1; // The default constructor will be called.

  return 0;
}
