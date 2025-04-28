/*

  ! Baseline:
  ! 1. `delete` the 4 methods if you don't know how to implement them.

*/

#include <utility>

//? 《因为太怕出错就全禁止了。》

struct Vector {
  int *data;

  //! 禁止拷贝构造：Vector vec1 = vec0。
  Vector(const Vector &) = delete;
  //! 禁止拷贝赋值：vec1 = vec0。
  Vector &operator=(const Vector &) = delete;

  //! 禁止“掠夺”构造：Vector vec1 = std::move(vec0)。
  Vector(Vector &&) = delete;
  //! 禁止“掠夺”赋值：vec1 = std::move(vec0)。
  Vector &operator=(Vector &&) = delete;

  ~Vector() { delete[] data; }
};

int main() {
  Vector vec0{new int[5]};

  // Vector vec1 = vec0;
  // Vector vec1 = std::move(vec0);

  //! 下集预告：
  //!   我们将学习如何正确地实现它们，而不是把它们禁止。
  //!   https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom.

  return 0;
}
