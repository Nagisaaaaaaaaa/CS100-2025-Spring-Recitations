#include <iostream>

class vec2f {
  // Construction
  //! 为什么这里我们无需自己手动写 拷贝/移动 的 构造/赋值 函数？
public:
  vec2f()
      : x_(0.0F)
      , y_(0.0F) {}

  vec2f(float x, float y)
      : x_(x)
      , y_(y) {}

  explicit vec2f(float x)
      : x_(x)
      , y_(x) {}

  // Public member functions
public:
  float &X() { return x_; }

  float &Y() { return y_; }

  float X() const { return x_; }

  float Y() const { return y_; }

  // Public Utils
public:
  friend void Print(const vec2f &vec) { std::cout << "{ " << vec.x_ << ", " << vec.y_ << " }" << std::endl; }

  // Private members
private:
  float x_;
  float y_;
};

int main() {
  vec2f A{1, 1};
  vec2f B{2, -1};
  A.X() += 20;
  Print(A);
  Print(B);

  return 0;
}
