/*

  ! Baseline:
  ! 1. Learn to wrap implementation details with namespaces.

*/

#include "namespace_02.h"
#include <iostream>

int main() {

  // 我们可以如愿访问到真正有用的函数：
  std::cout << major_func() << "\n";
  // 但同时我们没有任何直接访问到some_ugly_helper_func的手段

  // 除非我们显式地从名字空间里找：
  // -- 相当于溜进后厨偷吃块小蛋糕
  std::cout << detail::some_ugly_helper_func_0();

  // 或者暴力地把这个标明是实现细节的名字空间暴露出来：
  // -- 相当于溜进后厨吃 自 助 餐 ！（非常过分）
  using namespace detail; // But why, bro？

  // 但做出这样的行为本身，已经意味着用户
  // ! 非 常 清 楚 自 己 在 做 什 么
  // ! 非 常 清 楚 自 己 踏 入 了 灰 色 领 域
  // ! 并 愿 意 自 己 承 担 相 应 的 风 险

  // 我们无法真正制止用户做些什么
  // 但至少可以发布一份 `免责申明`

  // 和const一样，这是一种保护机制，是 `程序员之间的暗号`
  // 是防止各种各样 `行为艺术` 的第一道防线
  // 并不从根本上 `杜绝` `行为艺术` 的发生
  // 只是增加了 `行为艺术` 的实施成本
  // 从而起到良好的提醒作用————这就已经足够足够了

  // ! 自 由 和 安 全 是 有 本 质 矛 盾 的
  // ! 所 以 做 好 自 己 能 做 的 就 行

  return 0;
}
