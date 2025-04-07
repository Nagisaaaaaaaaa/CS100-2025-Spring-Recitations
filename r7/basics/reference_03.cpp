/*

  ! Baseline:
  ! 1. Read the following story and understand it.

*/

#include <iostream>
#include <vector>

// 《第二章：返回引用竟然是左值？有没有地址？可以被修改吗？》

// 如果说，在参数传递层面，【传址（指针）】和【传引用】并不具备本质性区别的话
// 那么在返回值层面，返回【地址】和返回【引用】则是天差地别：

// 传唤一位有名有姓的人物，把它家庭住址抄送出来
int *get_int_addr(int &x) {
  return &x;
}

// 传唤一名有名有姓的人物，然后返回它本体
int &get_int_self(int &x) {
  return x;
}

// 在静态存储区定义变量，它们的生命周期贯穿整个程序运行
int x = 42;
int y = 2025;

int main() {

  int *addr = get_int_addr(x); // 返回值显然仍然是个孤魂野鬼（右值）
  // 需要立刻挂靠到有名有姓的变量addr门下，否则就消逝了

  std::cout << ++(*addr) << "\n";            // 我们既可以通过这个地址去开盒
  std::cout << ++(*get_int_addr(x)) << "\n"; // 也可以再临时召唤一个孤魂野鬼来做这件事

  // 但无论如何，这个函数的返回值（正如我们习惯的那样）是一个右值，总是孤魂野鬼
  // 对它进行抓取地址，或者对它赋值等操作都是不允许的————因为它是临时的：
  // 你或许想过做以下这些事：
  /*

  get_int_addr(x) = &y;                    // 试图偷偷给x换成y的户口？
  get_int_addr(x)++;                       // 试图偷偷给x换成邻居的户口？
  int *const &addr_ref = &get_int_addr(x); // 给x的地址绑一个别称？

  */
  // 但这些统统不被允许！因为get_int_addr的返回值是【右值】，是孤魂野鬼
  // 它的生命如同风中残烛，你只能在 “ 享用 / 储存 / 抛弃 ” 这三者中立刻做出选择
  // 任何试图把它当作一个有名有姓的对象进行操作或修改的行为都会失败（因为本来也没有意义）

  // 但是！有一类函数返回值是例外————即返回引用

  std::cout << ++(get_int_self(y)) << "\n"; // 这个大家显然都能理解，但是……

  get_int_self(y) = 5202;        // 我们竟然在对函数返回值做赋值操作，不仅如此……
  int &y_ref = get_int_self(y);  // 还可以把一个引用绑定到函数返回值身上，更夸张的是……
  int *y_ptr = &get_int_self(y); // 还能取地址！不是流浪汉！这三者共同说明……
  // get_int_self的返回值并非右值！不是孤魂野鬼！而是一个活生生的，还具有一定寿命的变量！

  // ! 我的天哪，reference大人！
  // ! 在不动用黑魔法的情况下，这将是同学们接触的几乎唯一的函数返回左值的情况。

  std::cout << y << "\n"; // 5202

  return 0;
}
