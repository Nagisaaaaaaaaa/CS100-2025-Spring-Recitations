#include <type_traits>

//? 《Template/stay night》

// 我们来看下面这个模板特化的例子：

// Step 1: 默认情况下，定义 type 等于模板参数 T。
template <typename T>
struct remove_const {
  using type = T;
};

// Step 2: 对于 const 的模板参数，定义 type 等于 non-const 的版本。
template <typename T>
struct remove_const<const T> {
  using type = T;
};

// 神奇的事情发生了，我们可以用这个 struct 来：
//!  去掉模板参数中的 const。
static_assert(std::is_same_v<remove_const<int>::type, int>);
static_assert(std::is_same_v<remove_const<const int>::type, int>);

// 通过 using 来定义一个“快捷方式”。
template <typename T>
using remove_const_t = remove_const<T>::type;

static_assert(std::is_same_v<remove_const_t<int>, int>);
static_assert(std::is_same_v<remove_const_t<const int>, int>);

//* remove_const 和上一页的 is_int 一样，
//* 也被称为 type trait。
//*
//* 这两个例子分别对应了两种操作：
//* 1. is_int      : 提取特征。
//* 2. remove_const: 修改特征。
//*
//* 感受一下，我们所有的操作都是在“编译时”完成的，
//* 是不是很神奇。

//? 但助教，这一通操作下来，什么都没有发生，
//? 既然所有操作都是“编译时”的，那对“运行时”没有任何影响啊？
