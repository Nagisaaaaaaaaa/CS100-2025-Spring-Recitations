#include <iostream>

class Vector {
public:
  Vector() = default;

  Vector(size_t size) : data_((int *)malloc(sizeof(int) * size)), size_(size) {
    for (size_t i = 0; i < size; ++i)
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

  return 0;
}
