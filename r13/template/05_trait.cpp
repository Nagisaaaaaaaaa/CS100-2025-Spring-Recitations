#include <type_traits>

//? 《Template/stay night》

// 远在 r08/basics，我们学习过：
// 1. constexpr 的意思是“在编译时求值”。
// 2. 它可以跟 static_assert 配合使用。

// 我们来看下面这个模板特化的例子：

// Step 1: 默认情况下，定义一个编译时的 false。
template <typename T>
struct is_int {
  static constexpr bool value = false;
};

// Step 2: 当模板参数为 int 时，定义一个编译时的 true。
template <>
struct is_int<int> {
  static constexpr bool value = true;
};

// 神奇的事情发生了，我们可以用这个 struct 来：
//!  判断给定的模板参数是否是 int。
static_assert(is_int<int>::value == true);
static_assert(is_int<double>::value == false);

// 可以再定义一个模板变量来进一步简化调用 (快捷方式)。
template <typename T>
static constexpr bool is_int_v = is_int<T>::value;

static_assert(is_int_v<int> == true);
static_assert(is_int_v<double> == false);

//* 我们来总结一下发生了什么：
//* 1. 借助模板特化，我们定义了一个叫做 is_int 的 struct，
//*    它能够用于 判断给定的模板参数是否是 int。
//* 2. 可以再定义一个模板变量 is_int_v 来进一步简化调用 (快捷方式)。
//*
//* 感受一下 struct is_int，它能够提取模板参数的“特征”。
//* 在这个例子中，“特征”是指：是否是 int。
//*
//* 因此，struct is_int 这样的类型 被称为“type trait” (类型特征)。
//* 而我们此时正在学习的奇妙技术，叫做 metaprogramming (元编程)。
