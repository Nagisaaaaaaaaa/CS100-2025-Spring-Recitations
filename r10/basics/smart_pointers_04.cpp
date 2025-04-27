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

// 假设我们想实现一个函数，在给定的 Window 里面画画。
//! 函数参数怎么设计最合适？

void RenderSomethingInWindow(std::unique_ptr<Window> &window) {
  // ...
}

void RenderSomethingInWindow(std::shared_ptr<Window> &window) {
  // ...
}

void RenderSomethingInWindow(Window *window) {
  // ...
}
