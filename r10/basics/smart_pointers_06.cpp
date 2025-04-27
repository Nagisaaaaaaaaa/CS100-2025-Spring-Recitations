/*

  ! Baseline:
  ! 1. 函数参数能用裸指针就不要用智能指针。

*/

#include <iostream>
#include <memory>

class Window {
public:
  Window(int width, int height)
      : width_(width)
      , height_(height) {}

  ~Window() { std::cout << "Destructing the window" << std::endl; }

public:
  int width() const { return width_; }

  int height() const { return height_; }

private:
  int width_;
  int height_;
};

//? 《C++ 的超能力指针》

//! 我们在 r8/basics 学习过 pass-by-view 的设计思想，
// 当时的例子是 void Print(std::span<int> view)。
//! 所以，函数参数能用裸指针就不要用智能指针。

void RenderSomethingInWindow(Window *window) {
  // ...
}

int main() {
  auto window0 = std::make_unique<Window>(2560, 1440);
  auto window1 = std::make_shared<Window>(2560, 1440);

  RenderSomethingInWindow(window0.get());
  RenderSomethingInWindow(window1.get());

  return 0;
}
