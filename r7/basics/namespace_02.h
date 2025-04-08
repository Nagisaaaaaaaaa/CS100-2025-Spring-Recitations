/*

  ! Baseline:
  ! 1. Learn to wrap implementation details with namespaces.

*/

// 《拒绝成为暴露狂》

// 假设我们为了实现某个功能
// ————或屈服于ddl的淫威
// ————或受制于自己知识的局限
// ————或由功能本身的复杂性决定
// 需要用到一系列并不优雅的 `小帮手` 函数
// 它们功能线性而单一，除了服务于功能实现以外，没什么存在价值
// 你不希望这些 `理论上和核心功能无关的小帮手们`
// 在用户引用这份头文件时被一起带进名字空间
// 这个时候你可以用一层namespcae把他们包起来：

namespace detail {
int some_ugly_helper_func_0() {
  // 出于某种原因，你绝不希望这个小函数暴露给这份头文件的用户
  return 0;
}

int some_ugly_helper_func_1() {
  // 出于某种原因，你绝不希望这个小函数暴露给这份头文件的用户
  return 1;
}

int some_ugly_helper_func_2() {
  // 出于某种原因，你绝不希望这个小函数暴露给这份头文件的用户
  return 2;
}

int some_ugly_helper_func_3() {
  // 出于某种原因，你绝不希望这个小函数暴露给这份头文件的用户
  return 3;
}

} // namespace detail

// 但是你的主函数（用户事实上会调用的接口）用到了这些函数
int major_func() {
  return detail::some_ugly_helper_func_0() + detail::some_ugly_helper_func_1() + detail::some_ugly_helper_func_2() +
         detail::some_ugly_helper_func_3();
}
