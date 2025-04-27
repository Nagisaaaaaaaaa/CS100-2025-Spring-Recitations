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
    std::unique_ptr<Window> window = std::make_unique<Window>(2560, 1440);
    std::cout << "Width : " << window->width() << std::endl;
    std::cout << "Height: " << window->height() << std::endl;
  }

  {
    auto window = std::make_unique<Window>(2560, 1440);
    // ...
  }

  {
    auto window0 = std::make_unique<Window>(2560, 1440);
    // auto window1 = window0;
    auto window2 = std::move(window0);
  }

  return 0;
}
