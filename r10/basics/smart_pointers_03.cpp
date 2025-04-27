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
  // 我们有两种智能指针，unique_ptr 和 shared_ptr。
  //? 纯爱战士和牛头人。
  auto window0 = std::make_unique<Window>(2560, 1440);
  auto window1 = std::make_shared<Window>(2560, 1440);

  //! 这两种智能指针有什么区别？
  //! 1. 所有权：
  //     unique_ptr: 只有一个“所有者”。
  //     shared_ptr: 会有多个“所有者”。
  //! 2. 性能：
  //     unique_ptr: 巨无比快，和裸指针性能相同。
  //     shared_ptr: 会影响性能。

  //* 那么该如何选择用哪种呢？

  //* 结论：
  //* 1. 请永远选择 unique_ptr，因为
  //!    shared_ptr 会让生命周期非常混乱，
  //*    并且会影响性能。
  //* 2. 如果存在某个需求，
  //*    很不适合用 unique_ptr，但很适合用 shared_ptr，
  //*    那你就得考虑用 Python 去实现它，而不是 C++。
  //*    https://github.com/pybind/pybind11。

  return 0;
}
