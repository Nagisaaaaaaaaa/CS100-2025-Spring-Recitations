/*

  ! Baseline:
  ! 1. There is only one difference between `struct` and `class`:
  !   (1). `struct` members are public  by default.
  !   (2). `class`  members are private by default.
  ! 2. Constructors:
  !   (1). How to implement and call constructors.
  !   (2). Why "default" constructors are called "default"?
  ! 3. Member functions:
  !   (1). How to implement and call member functions.
  !   (2). `const` and non-`const` member functions.
  ! 4. Why `Vector vec2 = vec` is dangerous?

  * Bonus:
  * 4. It is usually better for all `struct` member variables to be public .
  * 5. It is usually better for all `class`  member variables to be private.

*/

#include <iostream>

class Vector {
public:
  Vector() = default;

  Vector(size_t size) : data_((int *)malloc(sizeof(int) * size)), size_(size) {
    for (size_t i = 0; i < size_; ++i)
      data_[i] = 0;
  }

  //* We will learn this next week.
  // Vector(const Vector &) = delete;
  // Vector &operator=(const Vector &) = delete;

  ~Vector() { free(data_); }

public:
  const int *data() const { return data_; }

  int *data() { return data_; }

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

  Vector vec1;       // The default constructor will be called.
  Vector vec2 = vec; //! Dangerous!.

  return 0;
}
