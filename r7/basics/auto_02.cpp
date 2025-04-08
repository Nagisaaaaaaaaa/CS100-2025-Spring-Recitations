/*

  ! Baseline:
  ! 1. Remember to use `auto` in ranged-based loop!
  * Bonus:
  * 2. Explore `std::pair<>`!
  * 3. Think about this: what the hell is std::make_pair ???

*/

#include "namespace_01.h"
#include <iostream>
#include <utility>
#include <vector>

// 接下来为大家介绍 `auto` 的第二个主要阵线，也就是循环内部

int main() {
  using namespace ShanghaiTech;

  // std::pair<Tx,Ty> 是标准库中提供的模板类型
  // 简单来说，当你规定了Tx, Ty两种类型后，它会为你生成一种新的类型
  // 这种类型可以装 “一对” Tx, Ty 类型的变量
  // 你可以通过first和second去访问里面的东西
  auto pair0 = std::pair<double, Student>(3.50, give_me_a_student());

  // 但是我们很快就发现，在构造这样的pair的时候
  // 思考 `这个pair究竟是什么类型` 是一件很掉san的事情，尤其是类型比较复杂的时候
  // 这个时候我们就希望编译器辅佐一下我们
  // 于是我们向 `auto` 之神祈祷，然后坐上了轮椅：
  auto pair1 = std::make_pair(3.95, give_me_a_student());
  // make_pair为什么可以返回各种类型的东西？ 它是何方神圣？

  // 现在假设你有很多这样的pair，然后你把它们装在一个vector内部
  std::vector<std::pair<int, std::string>> vec = {{1, "one"}, {2, "two"}};

  // 在只读遍历这种vector的过程中，你应该总是使用 const auto & ！
  // `auto`  保证了代码的简洁性，同时预防你任何可能产生的手动指定类型的错误
  //  `&`    避免了拷贝操作，节省了开销
  // `const` 保护了只读性，确保所有的pair不被错误更改
  for (const auto &p : vec) {
    std::cout << p.first << ": " << p.second << "\n";
  }

  // ! 这种写法将会是未来同学们使用最多的遍历循环，请务必熟记于心

  return 0;
}
