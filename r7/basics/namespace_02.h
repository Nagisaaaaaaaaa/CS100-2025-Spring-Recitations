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
// 我们不希望这些 `理论上和核心功能无关的小帮手们`
// 在用户引用这份头文件时被一起带进名字空间，行程污染
// 这个时候我们可以用一层namespcae把他们包起来：

namespace detail { // 这层名字空间就类似餐厅里，写着 `厨房重地 闲人免进` 的后厨

int some_ugly_helper_func_0() {
  // 出于某种原因，我们绝不希望这个小函数暴露给这份头文件的用户
  return 0;
}

int some_ugly_helper_func_1() {
  // 出于某种原因，我们绝不希望这个小函数暴露给这份头文件的用户
  return 1;
}

int some_ugly_helper_func_2() {
  // 出于某种原因，我们绝不希望这个小函数暴露给这份头文件的用户
  return 2;
}

int some_ugly_helper_func_3() {
  // 出于某种原因，我们绝不希望这个小函数暴露给这份头文件的用户
  return 3;
}

} // namespace detail

// 但是你的主函数（用户事实上会调用的接口）用到了这些函数。
// 这是我们端上来的菜肴，用户只负责享受就行了，平时不需要也不应该去窥探后厨
int major_func() {
  using namespace detail; // 我们自己烹饪当然可以进后厨
  return some_ugly_helper_func_0() + some_ugly_helper_func_1() + some_ugly_helper_func_2() + some_ugly_helper_func_3();
} // 烹饪完再离开后厨
