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
    std::shared_ptr<Window> window = std::make_shared<Window>(2560, 1440);
    std::cout << "Width : " << window->width() << std::endl;
    std::cout << "Height: " << window->height() << std::endl;
  }

  {
    // 用 auto 来让代码写得更短。
    auto window = std::make_shared<Window>(2560, 1440);
    // ...
  }

  {
    //! 那我问你，这里总共有几个窗口？
    auto window0 = std::make_shared<Window>(2560, 1440);
    auto window1 = window0; //! 让两个智能指针指向同一个窗口。
    auto window2 = std::move(window0);

    //? 所以 shared_ptr 是“牛头人”。
  }

  {
    //! 那我问你，谁真正拥有这个窗口？
    auto window = std::make_shared<Window>(2560, 1440);
    Window *ptr = window.get();
  }

  // 有没有感受到一点违和？
  //   auto window0 = std::make_shared<Window>(2560, 1440);
  //   auto window1 = window0; //! 让两个智能指针指向同一个窗口。
  //
  //! 谁真正拥有这个窗口？
  //   window0 和 window1 都拥有这个窗口。
  //   我们目前为止看到所有的 RAII 例子中，都只有一个“所有者” (owner)。
  //   这是第一次出现了多个“所有者”。
  //
  //! 谁负责调用 Window 的析构函数？
  //   最后一个拥有 Window 的“所有者”会调用析构析构函数。

  //* 凭我们现在的知识储备，手搓 unique_ptr 绰绰有余，
  //* 但可以想象，shared_ptr 是个超级复杂的东西，远远超纲了。

  return 0;
}
