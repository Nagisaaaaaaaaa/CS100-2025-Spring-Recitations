/*

  ! 请使用 g++ -std=c++20 来编译。

  ! 我们已经学到了哪几种“资源管理”方法？
  ! Baseline:
  ! 1. 存在唯一“所有者”的管理方法 (纯爱战士)。
  ! 2. 存在多个“所有者”的管理方法 (牛头人)。
  * Bonus:
  * 3. 不存在任何“所有者”的管理方法 (散养)？见 r7/supp。

*/

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

  //! 1. 存在唯一“所有者”的管理方法 (纯爱战士)。
  std::vector<Window> windows0;
  std::unique_ptr<Window> window1;

  //! 2. 存在多个“所有者”的管理方法 (牛头人)。
  std::shared_ptr<Window> window2;

  // 实际上，远在 r7，我们就给大家见识过第 3 种。见 r7/supp。

  //* 3. 不存在任何“所有者”的管理方法 (散养)？
  Window *window3 = new Window{2560, 1440};
  Window *window4 = new Window{3840, 2160};

  //* 那我问你，谁真正拥有这些窗口？
  //* 没有任何人拥有它们！
  std::cout << Window::size() << std::endl;

  for (Window &window : Window::range()) {
    std::cout << "Width : " << window.width() << std::endl;
    std::cout << "Height: " << window.height() << std::endl;
  }

  //* 有趣的是，Registry 能够让 new 和 delete 变得非常安全。
  while (Window::size() > 0) {
    Window &window = *Window::begin();
    delete &window;
  }

  std::cout << Window::size() << std::endl;

  //! 那么如何选择该使用哪种管理方式呢？
  //! 1. 请永远优先选择“纯爱战士”。
  //* 2. 如果觉得“散养”很香，也可以选择它。
  //! 3. 请尽量不要选择“牛头人”。

  return 0;
}
