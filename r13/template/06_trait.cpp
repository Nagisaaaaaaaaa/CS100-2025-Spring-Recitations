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
