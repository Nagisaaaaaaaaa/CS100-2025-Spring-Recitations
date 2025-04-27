/*

  ! Baseline:
  ! 1. 为什么 C++ 需要引入智能指针？

*/

#include <iostream>
#include <vector>

// 假设我们在做游戏开发，当然需要有“窗口”这样的类型。

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

int main() {
  //? 《C++ 的超能力指针》

  // 我们只需要一个 Window，又希望它被存储在堆上，
  // 这不会要弄一个 size = 1 的 std::vector 吧？
  std::vector<Window> window;

  //! size = 1 其实是个很常见的需求。
  // 回顾一下 HW4，map、config、game 都需要这个功能。

  //! 因此，C++ 给 size = 1 提供了一系列的“快捷方式”，
  //! 它们就是所谓的“智能指针”。

  return 0;
}
