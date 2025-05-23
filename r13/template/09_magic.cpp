#include "../../r08/supp/ARIA/TypeArray.h"

//? 《Template/stay night》

//* 编程小知识：
//*   我们已经见识到了 metaprogramming (元编程) 的魅力，
//*   那么元编程最不可或缺的“基础设施”是什么呢？
//*   我相信它是 TypeArray，
//*
//*   TypeArray 是一个编译时的，包含了各种类型的数组。
//*   我们能够自由操纵 (访问、修改) 里面的各种类型。

using Ts = ARIA::MakeTypeArray<int, unsigned, float, double>;
static_assert(std::is_same_v<Ts::Get<0>, int>);
static_assert(std::is_same_v<Ts::Get<1>, unsigned>);
static_assert(std::is_same_v<Ts::Get<2>, float>);
static_assert(std::is_same_v<Ts::Get<3>, double>);

using Ts1 = Ts::PushBack<std::string>;
static_assert(std::is_same_v<Ts1::Get<4>, std::string>);

int main() {
  ARIA::ForEach<Ts1>([]<typename T> { //
    std::cout << typeid(T).name() << std::endl;
  });

  return 0;
}
