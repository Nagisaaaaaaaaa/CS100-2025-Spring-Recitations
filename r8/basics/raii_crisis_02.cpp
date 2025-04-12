/*

  ! Baseline:
  ! 1. Why moving "RAII owner" is dangerous.

*/

#include <type_traits>

//? 《Ban Dream! It's My构!!!!!》

// 请找到这几行代码中的 bug。

struct Vector {
  int *data;

  ~Vector() { delete[] data; }
};

int main() {
  Vector vec0{new int[5]};

  // 和 C 语言的规则一样，这行代码相当于 vec1.data = vec0.data。
  Vector vec1 = vec0;

  //! 那么 bug 在哪儿？
  //!   这两个 Vector 的 data 指向了同一段内存，
  //!   当它们的析构函数被调用时，会对同一段内存 delete 两次。
  //!   这会导致 undefined behavior，连 try-catch 都救不了！

  return 0;
}
