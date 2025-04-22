/*

  ! Baseline:
  ! 理解这重要的一课。
  ! 但是不要照搬助教代码然后submit~

*/

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
      , data_(size_ ? new int[size_] : nullptr) {
    for (size_type k = 0; k < size_; ++k) {
      data_[k] = 0;
    }
  }

  // Construct by length & value
  Dynarray(size_type size, int val)
      : size_(size)
      , data_(size_ ? new int[size_] : nullptr) {
    for (size_type k = 0; k < size_; ++k) {
      data_[k] = val;
    }
  }

  // Construct by span
  Dynarray(const int *begin, const int *end)
      : size_((end - begin) > 0 ? (end - begin) : 0)
      , data_(size_ ? new int[size_] : nullptr) {
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
    other.size_ = 0;
  }

  //! 为了一口气解决上一版实现中的三个痛点
  //! 一群C++仙人苦思冥想，然后发明了下面这种写法
  //! 首先我们抽象出赋值中最关键（同样也是最安全）的一步：交换数据
  friend void swap(Dynarray &alice, Dynarray &bob) noexcept {
    using std::swap;
    swap(alice.size_, bob.size_);
    swap(alice.data_, bob.data_);
  }

  //! 然后我们发现————海阔天空

  // Assignments (Move)
  Dynarray &operator=(Dynarray &&other) noexcept {
    //! 很显然，移动赋值就是把一个右值（孤魂野鬼）里面装着的内容
    //! 塞到有名有姓的 `*this` 名下，这个过程一个swap就给解决了
    swap(*this, other);
    return *this;
  }

  // Assignments (Copy)
  Dynarray &operator=(const Dynarray &other) {
    //! 拷贝赋值唯一的区别是，不能改动参数本尊
    //! 那我们就临时给他捏出一个替身兄弟，然后继续swap进 `*this`
    Dynarray copy = other;
    swap(*this, copy);
    return *this;
  }

  //* 仔细思考你会发现，事实上我们可以进一步把两种赋值整合成为：
  //* 这种写法巧妙地利用了传value的语义，自动适配了左值右值两种版本
  //* （拓展思考题1）这是为什么？
  //* （拓展思考题2）
  // Assignments (Move & Copy)
  Dynarray &operator=(Dynarray other) {
    swap(*this, other);
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
