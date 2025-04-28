/*

 ! Baseline:
 ! 1. Understand the following example

*/

#include <iostream>

//* For each lambda object, the capture happens at the time the lambda object is created
//* — and each lambda object keeps its own copy (or reference) of the captured variables.
//* Thus, the capture is executed once at construction, not every time the lambda is called.

//* （并不非常）聪明的爱音同学反复阅读了这段文字，恍然大悟：
//*  我们知道函数每次调用的时候都会发生传参，那么，
//*  既然并非每次 `调用` 的时候都执行 `捕获`，就说明
//!  捕获本质上不是一种典型的参数传递行为
//*  爱音继续思考，那什么东西是只需要被调用一次，便能把一种状态 / 信息 维持在程序中呢？
//*  没错，也就是构造！
//!  换句话说，所谓 `捕获`，本质上是说在 `构造` lambda对象的一瞬间
//!  从当前的 namescope 捕获一些东西，成为类似于lambda成员变量一样的存在

//* [ capture_list ] ( parameter_list ) -> return_type { body }
//* [ 这里的东西是路上捡的成员变量 ]
//* ( 这里的东西是真正函数的参数 )
//* { 函数体，没什么花样 }

//*  为了让爱音同学更加理解捕获这个概念，以及mutable关键字的作用
//*  我们借助 Lec20第35页 （包括我们刚才也讲到过的Functor）概念进行解析

int main() {
  int x = 42;
  int y = 2025;
  std::string s = "Ave Mujica";

  auto func_1 = [x, &y, s = std::move(s)]() {
    // Blablabla
    // More blablabla
  };

  // The above lambda is essentially the same as:
  class Functor {
  public:
    Functor(int x, int &y, std::string s)
        : x_(x)
        , y_(y)
        , s_(std::move(s)) {}

    void operator()() {
      // Blablabla
      // More blablabla
    }

  private:
    //! Captured-by-value variables are const by default;
    //! `mutable` removes this restriction
    const int x_;
    int &y_;
    std::string s_;
  };

  std::string s2 = "Random other string"; // Fresh string to avoid moved-from s
  Functor func_2{x, y, std::move(s2)};

  //* func_1 and func_2 are almost equivalent in structure.
  //* 于是千早爱音完成了对于lambda的上手，节省了许多未来debug的时间！
  //* 因此 MyGO!!!!! 乐队大获成功！
}
