#include <vector>

//? 《Template/stay night》

// 假设我们已经实现了默认版本的 Dynarray。
// 但又懒得自己实现 bool 版的 Dynarray，
//! 有没有办法直接“偷” std::vector<bool> 来用呢？
//
// 换句话说：
// 1. 当模板参数不是 bool 时，用我们自己写的 Dynarray。
// 2. 当模板参数是 bool 时，用 std::vector<bool>。

//
//
//
//
//
// 答案：

// 我们将 Dynarray 重命名为 DynarrayImpl。
template <typename T>
class DynarrayImpl {
  // ...
};

// 定义一个叫做 deduce 的 type trait。
// Step 1: 默认情况下，选择 DynarrayImpl。
template <typename T>
struct deduce {
  using type = DynarrayImpl<T>;
};

// Step 2: 当模板参数为 bool 时，选择 std::vector<bool>。
template <>
struct deduce<bool> {
  using type = std::vector<bool>;
};

//! 于是，我们真正的 Dynarray 其实是个 using。
template <typename T>
using Dynarray = deduce<T>::type;

int main() {
  Dynarray<int> v0;
  Dynarray<bool> v1;

  static_assert(std::is_same_v<Dynarray<int>, DynarrayImpl<int>>);
  static_assert(std::is_same_v<Dynarray<bool>, std::vector<bool>>);

  //* 感受一下这个例子。
  //*
  //* 我们此时正在学习的奇妙技术，叫做 metaprogramming (元编程)。
  //* 它的核心思想是：利用编译器在编译阶段执行代码，从而生成最终的运行时代码。
  //*
  //* 在 C++ 中，模板特化 几乎是元编程的必经之路，这就是为什么说：
  //!   模 板 特 化 是 C++ 最 伟 大 的 语 法 ！

  //! 此刻，我们总算是真正地，“入门” C++ 了！

  return 0;
}
