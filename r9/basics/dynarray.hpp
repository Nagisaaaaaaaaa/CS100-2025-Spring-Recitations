#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>

class Dynarray {
  using size_type = std::size_t;

public:
  // Default constructor
  Dynarray() = default;

  // Destructor
  ~Dynarray() { delete[] data_; }

  // Construct by length
  explicit Dynarray(size_type size)
      : size_(size)
      , data_(new int[size_]) {
    for (size_type k = 0; k < size_; ++k) {
      data_[k] = 0;
    }
  }

  // Construct by length & value
  Dynarray(size_type size, int val)
      : size_(size)
      , data_(new int[size_]) {
    for (size_type k = 0; k < size_; ++k) {
      data_[k] = val;
    }
  }

  // Construct by span
  Dynarray(const int *begin, const int *end)
      : size_((end - begin) > 0 ? (end - begin) : 0)
      , data_(new int[size_]) {
    for (size_type k = 0; k < size_; ++k) {
      data_[k] = begin[k];
    }
  }

  // Copy constructor
  Dynarray(const Dynarray &other)
      : size_(other.size_)
      , data_(new int[other.size_]) {
    for (size_type k = 0; k < size_; ++k) {
      data_[k] = other.data_[k];
    }
  }

  // Move constructor
  Dynarray(Dynarray &&other) noexcept
      : size_(other.size_)
      , data_(other.data_) {
    other.data_ = nullptr;
  }

  // Copy assignment
  Dynarray &operator=(const Dynarray &other) {
    if (&other == this) {
      return *this;
    }

    size_type new_size = other.size_;
    int *new_data = new int[new_size];
    for (size_type k = 0; k < new_size; ++k) {
      new_data[k] = other.data_[k];
    }
    delete[] data_;
    size_ = new_size;
    data_ = new_data;
    return *this;
  }

  // Move assignment
  Dynarray &operator=(Dynarray &&other) noexcept {
    if (&other == this) {
      return *this;
    }
    delete[] data_;
    size_ = other.size_;
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
  }

public:
  size_type size() const { return size_; }

  bool empty() const { return size_ == 0; }

  int &at(size_type n) {
    if (n >= size_) {
      throw std::out_of_range{"Dynarray index out of range!"};
    }
    return data_[n];
  };

  const int &at(size_type n) const {
    if (n >= size_) {
      throw std::out_of_range{"Dynarray index out of range!"};
    }
    return data_[n];
  };

private:
  size_type size_ = 0;
  int *data_ = nullptr;
};

#endif // DYNARRAY_HPP
