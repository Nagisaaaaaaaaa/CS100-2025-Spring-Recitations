#include "../../r07/supp/ARIA/Registry.h"

//? 《Template/stay night》

//* 编程小知识：
//*   我们的老朋友 Registry 其实有个更官方的名字，“侵入式链表”。
//*   ARIA Registry 是通过一种叫做 CRTP (Curiously Recurring Template Pattern)
//*   的模板小技巧实现的。

//* 父类的模板参数竟然是子类？
class Window : public ARIA::Registry<Window> {
public:
  Window(int width, int height)
      : width_(width)
      , height_(height) {}

public:
  using Base = ARIA::Registry<Window>;
  using Base::begin;
  using Base::end;
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
  for (Window &window : Window::range()) {
    std::cout << "Width : " << window.width() << std::endl;
    std::cout << "Height: " << window.height() << std::endl;
  }

  return 0;
}
