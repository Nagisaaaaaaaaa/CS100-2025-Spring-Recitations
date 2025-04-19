#include <iostream>

//? 《右值终末旅行》第二季

void Print(const std::string &str) {
  std::cout << str + "!" << std::endl;
}

void Print(std::string &&str) {
  str += "!";
  std::cout << str << std::endl;
}

void Go(const std::string &str) {
  // 那我问你，这里会调用哪个重载？
  Print(str);
}

void Go(std::string &&str) {
  //! C++ 选择重载，是由“表达式”的“类别”来决定的！
  //! 所以，如果我们希望它调用 && 的版本，
  //! 就得将“表达式”的“类别”变成 右值 (rvalue)。

  // 比如这么做，我们通过拷贝构造函数，
  // 对字符串做一次拷贝，就能得到一个右值。
  // 这样就能调用 && 的那个版本了。
  // Print(std::string(str));

  // 但很多时候，我们不希望做拷贝。
  // 比如这个例子，最优解一定是不需要任何拷贝的。

  //! 还记得我们上节课介绍了 std::move，它能够“把拷贝换成掠夺”，
  //* 我们也提到过，std::move(str) 这个“表达式”的“类别”是
  //*   将亡值 (expiring value, xvalue)。
  //* 我们还提到过，将亡值 (xvalue) 是一种 右值 (rvalue)。

  //! 那我问你，这里会调用哪个重载？
  Print(std::move(str));

  // 分析一波这行代码发生了什么？
  //! 1. 我们通过 std::move(str) “掠夺”了 str，
  //!    并创建了一个“类别”为 右值 的“表达式”。
  //! 2. 接着我们调用了 Print，因为传入的是右值，
  //!    编译器会选择 && 版本的 Print (开后门)。
  //! 3. Print 的参数是 &&，它能延长右值的生命周期，
  //!    所以，std::move(str) 的生命周期被延长了。
}

int main() {
  // 那我问你，这里会调用哪个重载？
  std::string str("QAQ");
  Go(str);

  // 那我问你，这里会调用哪个重载？
  Go(std::string("QAQ"));

  //! 同样的，Go 也可以配合 std::move 来使用。
  //! 那我问你，这里会调用哪个重载？
  Go(std::move(str));

  // 我们再来仔细审视以下 && 版本的 Go 函数：
  //
  // 定义：
  //   void Go(std::string &&str) {
  //     Print(std::move(str));
  //   }
  //
  // 调用：
  //   Go(std::string("QAQ"));
  //   Go(std::move(str));
  //
  //* 可以感受到，输入的右值，每一层函数调用，都会被“掠夺”一次。
  //* 或者换一个更阳光的说法，每一层函数调用，都会被“移动”一次。
  //* 这就是 std::move 这个函数的名字由来。

  //! 总结一波：
  //! 1. C++ 为了避免函数重载导致的 ambiguity，引入了右值引用这种“类型”。
  //! 2. 右值引用不是什么神秘的东西，它们拥有和普通引用 (左值引用) 类似的游戏规则。
  //! 3. 为什么 拷贝/移动 构造/赋值 函数的参数分别是 const & 和 &&。
  //! 4. C++ 选择重载，是由“表达式”的“类别”来决定的。
  //! 5. 这就是为什么当我们需要掠夺时候，每一层都需要调用 std::move。

  return 0;
}
