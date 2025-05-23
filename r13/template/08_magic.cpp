#include "../../r08/supp/ARIA/ForEach.h"

//? 《Template/stay night》

//* 接下来，我们来欣赏一些模板相关的魔法。
//* 介绍这些魔法的目的是，让同学们能够体会到
//* 这门编程语言的强大之处。

int main() {
  //* 编程小知识：
  //*   当 for 循环的循环次数在“编译时”能够确定时，
  //*   例如，我们在“编译时”已知某个循环一定会跑 5 次。
  //*   这种情况下，将循环“展开”有时会让代码跑得更快。

  //! 这是个“普通”的循环。
  for (int i = 0; i < 5; ++i) {
    std::cout << i << std::endl;
  }

  //! 这是个“被展开”的循环。
  {
    std::cout << 0 << std::endl;
    std::cout << 1 << std::endl;
    std::cout << 2 << std::endl;
    std::cout << 3 << std::endl;
    std::cout << 4 << std::endl;
  }

  //! 这个写法完全等价于“被展开”的循环。
  ARIA::ForEach<5>([]<int i> { //
    std::cout << i << std::endl;
  });

  return 0;
}
