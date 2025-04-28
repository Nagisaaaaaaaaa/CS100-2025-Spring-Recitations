#include "../../r7/supp/ARIA/Registry.h"
#include <memory>
#include <vector>

class Window : public ARIA::Registry<Window> {
public:
  Window(int width, int height)
      : width_(width)
      , height_(height) {}

  ~Window() { std::cout << "Destructing the window" << std::endl; }

public:
  using Base = ARIA::Registry<Window>;
  using Base::begin;
  using Base::range;
  using Base::size;

public:
  int width() const { return width_; }

  int height() const { return height_; }

private:
  int width_;
  int height_;
};

int main() {
  //? 《C++ 的超能力指针》

  // 至此，我们已经学到了这几种“内存管理”方法，
  // 或者更通用的，我们称之为“资源管理”方法。

  //! 1. 拥有唯一“所有者”的管理方法 (纯爱战士)。
  std::vector<Window> windows0;
  std::unique_ptr<Window> window1;

  //! 2. 拥有多个“所有者”的管理方法 (牛头人)。
  std::shared_ptr<Window> window2;

  //* 3. 不存在“所有者”的管理方法 (野生)？见 r7/supp。
  Window *window3 = new Window{2560, 1440};
  Window *window4 = new Window{3840, 2160};

  //* 那我问你，谁真正拥有这些窗口？
  //* 没有任何人拥有它们！
  std::cout << Window::size() << std::endl;

  for (Window &window : Window::range()) {
    std::cout << "Width : " << window.width() << std::endl;
    std::cout << "Height: " << window.height() << std::endl;
  }

  //* 我们说过，在 C++ 中不建议手动 new 和 delete，
  //* 但为什么 Registry 能够让这件事情变得很安全？
  while (Window::size() > 0) {
    Window &window = *Window::begin();
    delete &window;
  }

  std::cout << Window::size() << std::endl;

  return 0;
}
