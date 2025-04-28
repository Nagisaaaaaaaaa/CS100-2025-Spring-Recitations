/*

  ! Baseline:
  ! 1. Understand the basic use of auto.

*/

#include "namespace_01.h"
#include <iostream>
#include <map>
#include <vector>

// 一言以蔽之，auto最基础（同时也是最广泛）的作用就是：
// 1. 简化我们的类型声明，使得代码清晰简洁；
// 2. 利用编译器自动推断，减少我们面对复杂类型时犯错的概率；

int main() {

  // 召唤一只具有复杂类型的对象
  std::map<std::string, std::vector<int>> umap;

  // 它对应的【迭代器】（之后大家会学）拥有更加冗长的类型描述
  // 如果不用auto的话，想要把返回的迭代器（右值）赋予一个新声明的变量就必须：

  std::map<std::string, std::vector<int>>::iterator iter0 = umap.begin();

  // 如果用auto的话
  auto iter1 = umap.begin();

  // 同样的，假设一个所需要的类型嵌套在了一个很深的名字空间中
  // 普通的做法是直接using这个类型，例如：
  {
    using ShanghaiTech::SIST::CS100::Recitation;
    Recitation r = ShanghaiTech::SIST::CS100::random_rclass();
  }

  // 或者直接引入需要的名字空间来干活（不推荐）
  {
    using namespace ShanghaiTech::SIST::CS100;
    Recitation r = random_rclass();
  }

  // 但上面两种做法不仅都有【污染命名空间】的可能，并且很多时候都是非必要的
  // 这个时候用auto来引用这个类型就是很合适的做法：
  auto r0 = ShanghaiTech::SIST::CS100::random_rclass();
  // 这样既保证了名字空间的纯净，也避免了写成：
  ShanghaiTech::SIST::CS100::Recitation r1 = ShanghaiTech::SIST::CS100::random_rclass();

  return 0;
}
