#include <cstdint>

//? 《Template/stay night》

//* 还记得远在 r09/supp，我们介绍了“代理” (proxy)。
//* 当时提到，std::vector<bool> 实际上只使用 1 个 bit 来存储 bool，
//* 这么设计是为了节省内存。

//* 那么，如何为我们的 Dynarray 实现类似的功能呢？
//! 也就是说，我们希望特殊处理 模板参数为 bool 的情况。
//! 而 C++ 允许“模板特化” (template specialization)，
//! 因此能够很轻松地做到这件事情。

// 这是我们的默认情况。
template <typename T>
class Dynarray {
public:
  // ...

private:
  T *data_ = nullptr;
  size_t size_ = 0;
};

//! 模板特化：特殊处理 模板参数为 bool 的情况
template <>
class Dynarray<bool> {
public:
  //! 允许定义不同的成员函数。
  // ...

private:
  //! 允许定义不同的成员变量。
  //   因为我们希望用 1 个 bit 来存储 bool，
  //   所以数据类型为 32 位的 unsigend 整型。
  //   我们需要通过位运算来修改其中的 bit。
  uint32_t *data_ = nullptr;
  size_t size_ = 0;
};

int main() {
  // 模板参数为 int 时，会优先选择“默认”的版本。
  Dynarray<int> v0;
  // 模板参数为 bool 时，会优先选择“特化”的版本。
  Dynarray<bool> v1;

  //* 注：C++20 引入了伟大的 concept，允许我们“更自由”地做特化，
  //*    例如可以为“所有整数类型的模板参数”做特化。
  //*    但我们不会介绍它，这太超纲了。

  //? 至此，我们已经学会了简单的模板特化，好像也没那么难嘛。
  //? 但实际上，助教可以断言：
  //?   模 板 特 化 是 C++ 最 伟 大 的 语 法 ！

  //? 此刻，我们即将真正地，“入门” C++。
}
