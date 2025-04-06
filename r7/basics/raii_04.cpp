#include <cstdlib>

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
  //* We will learn this next week.
  // const int *data() const { return data_; }

  int *data() { return data_; }

  size_t size() const { return size_; }

private:
  int *data_ = nullptr;
  size_t size_ = 0;
};

int main() {
  Vector vec(5);

  int *data = vec.data();

  return 0;
}
