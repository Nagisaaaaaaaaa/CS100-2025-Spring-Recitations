#include <cstddef>

//? 《Template/stay night》

//! 什么是模板 (template)？
//   在任何一个 struct/class 前面加上 template <typename T>，
//   就能把这个 struct/class 变成一个 template。
// 这里的 T 被称为模板参数 (template parameter)：
//   当我们写 Dynarray<int>    时，T 就是 int   ，得到 int    *data_。
//   当我们写 Dynarray<double> 时，T 就是 double，得到 double *data_。
template <typename T>
class Dynarray {
public:
  Dynarray() = default;

private:
  T *data_ = nullptr;
  size_t size_ = 0;
};

// 类似地，也可以定义模板函数。
template <typename T>
void Print(const Dynarray<T> &v) {}

// 模板参数不仅可以是类型，也可以是“数字”，
// 例如这里的 size_t n。
template <typename T, size_t n>
class Vec {
public:
  Vec() = default;

private:
  T v_[n];
};

int main() {
  Dynarray<int> arr;

  //! 当我们写下 Dynarray<int> 时，发生了什么？
  //
  // 答案：
  //!  编译器把模板 Dynarray 中所有的 T 都替换成了 int，
  //!  并且生成了一个新的类型。

  //! 那我问你：
  //   1. Dynarray      是一个“类型”吗？
  //   2. Dynarray<int> 是一个“类型”吗？

  // 答案是：
  //   1. Dynarray      不是一个“类型”，它是一个“模板”。
  //   2. Dynarray<int> 是一个“类型”没错。
  //
  // 我们称，从“模板”生成“类型”的过程，叫做：
  //   模板实例化 (template instantiation)。

  Print<int>(arr); //! 也可以简写为 Print(arr)。

  Vec<int, 3> v;

  return 0;
}
