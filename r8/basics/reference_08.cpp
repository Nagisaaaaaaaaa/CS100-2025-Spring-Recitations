/*

  ! Baseline:
  ! 1. Use `std::move` to “把拷贝换成掠夺”。

*/

#include <iostream>

int main() {
  {
    // 默认情况下，str1 = str0 会做个拷贝。
    std::string str0("QAQ");
    std::string str1 = str0;

    std::cout << str0.length() << std::endl;
    std::cout << str1.length() << std::endl;
  }

  {
    //! 但是，使用 std::move，我们就能“把拷贝换成掠夺”。
    std::string str0("QAQ");
    std::string str1 = std::move(str0);

    //! 这里 str0 已经被“掠夺”了，一无所有，所以 length 是 0。
    std::cout << str0.length() << std::endl;
    std::cout << str1.length() << std::endl;
  }

  //! 至此，我们已经见识到了三种写法：
  //! 1. std::string str1 = std::string("QAQ");
  //! 2. std::string str1 = str0;
  //! 3. std::string str1 = std::move(str0);
  //!
  //! 这三个等于号的含义分别是：
  //! 1. “孤魂野鬼找地方住”
  //! 2. 拷贝
  //! 3. “掠夺”

  //* 我们可以猜到，一定是这三个等号右边的东西存在差异，
  //* 导致了等号的行为发生变化。
  //*
  //* 我们知道：
  //* 1. std::string("QAQ") 是右值 (孤魂野鬼)。
  //* 2. str0               是左值 (有名有姓)。
  //*
  //* 注意哦，这里所说的左值、右值，都是“表达式的类别”，
  //* 和“变量的类型”没有任何关系。
  //* 更具体地说：
  //* 1. std::string("QAQ") 这个表达式的“类别”是 右值 (孤魂野鬼)。
  //* 2. str0               这个表达式的“类别”是 左值 (有名有姓)。
  //*
  //* 等等，不对啊，这个世界上不是只有左值和右值吗？
  //* 那 std::move(str0) 是什么呢？

  //* 其实故事是这样的：
  //* std::string("QAQ") 准确的名字叫做 纯右值 (pure r-value, prvalue)
  //* std::move(str0)    准确的名字叫做 将亡值 (expiring value, xvalue)
  //* 这两者统称为 右值 (rvalue)
  //*
  //* 也就是说：
  //* 1. C++ 的表达式可以分为 lvalue，prvalue，xvalue 三种“类别”。
  //* 2. 其中 prvalue 和 xvalue 这两种“类别”统称为 rvalue。
  //*
  //* 这就是所谓的 value category：
  //* https://en.cppreference.com/w/cpp/language/value_category

  //* 下集预告：
  //* 我们将会在下周介绍神秘的第三种“类别”，将亡值，xvalue。

  return 0;
}
