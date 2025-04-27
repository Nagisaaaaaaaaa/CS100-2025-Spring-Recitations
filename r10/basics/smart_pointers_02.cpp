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
  {
    std::shared_ptr<Window> window = std::make_shared<Window>(2560, 1440);
    std::cout << "Width : " << window->width() << std::endl;
    std::cout << "Height: " << window->height() << std::endl;
  }

  {
    auto window = std::make_shared<Window>(2560, 1440);
    // ...
  }

  {
    //! 那我问你，这里总共有几个窗口？
    auto window0 = std::make_shared<Window>(2560, 1440);
    auto window1 = window0;
    auto window2 = std::move(window0);
  }

  {
    //! 那我问你，谁真正拥有这个窗口？
    auto window = std::make_shared<Window>(2560, 1440);
    Window *ptr = window.get();
  }

  return 0;
}
