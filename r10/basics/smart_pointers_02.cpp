/*

  ! Baseline:
  ! 1. std::unique_ptr 是一种“纯爱战士”风格的智能指针。

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

int main() {
  //? 《C++ 的超能力指针》

  {
    std::unique_ptr<Window> window = std::make_unique<Window>(2560, 1440);
    std::cout << "Width : " << window->width() << std::endl;
    std::cout << "Height: " << window->height() << std::endl;
  }

  {
    // 用 auto 来让代码写得更短。
    auto window = std::make_unique<Window>(2560, 1440);
    // ...
  }

  {
    //! 那我问你，这里总共有几个窗口？
    auto window0 = std::make_unique<Window>(2560, 1440);
    // auto window1 = window0;
    auto window2 = std::move(window0);

    //? 所以 unique_ptr 是“纯爱战士”。
  }

  {
    //! 那我问你，谁真正拥有这个窗口？
    auto window = std::make_unique<Window>(2560, 1440);
    Window *ptr = window.get();
  }

  return 0;
}
