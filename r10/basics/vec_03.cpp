#include <cmath>
#include <iostream>

//! 这个文件中我们来处理乘法
//! 我们注意到，向量的乘法分为两种：
//! 数乘 a * {x, y} = {ax, ay}
//! 点乘 {x1, y1} \dot {x2, y2} = x1x2 + y1y2
//! 这样一来就出现了两种思路：
//! 1. 把 `*` 重载给数乘和点乘，根据参数类型自动判断
//! 2. 只把 `*` 重载給数乘，点乘用另一个单独的函数来表示
//! 在类似类型的设计中，我们应该永远采用思路2
//! 出于 `类型的安全与清晰` 以及 `与主流数学库匹配` 的考量

//

class vec2f {
  // Construction
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

  // Operator overloading
public:
  // Binary + overloading
  friend vec2f operator+(const vec2f &alice, const vec2f &bob) { return {alice.x_ + bob.x_, alice.y_ + bob.y_}; }

  // Unary - overloading
  vec2f operator-() const { return {-x_, -y_}; }

  // Binary - overloading
  friend vec2f operator-(const vec2f &alice, const vec2f &bob) { return alice + (-bob); }

  // Scalar * overloading (vec * s)
  vec2f operator*(float s) const { return {x_ * s, y_ * s}; }

  // 别忘了另外实现左乘！
  // Scalar * overloading (s * vec)
  friend vec2f operator*(float s, const vec2f &vec) { return vec * s; }

  // Binray dot
  friend float dot(const vec2f &alice, const vec2f &bob) { return (alice.x_ * bob.x_) + (alice.y_ * bob.y_); }

  // Public Utils
public:
  friend void Print(const vec2f &vec) { std::cout << "{ " << vec.x_ << ", " << vec.y_ << " }" << std::endl; }

  //! 实现了dot之后我们很自然可以计算模长
  friend float abs(const vec2f &vec) { return sqrtf(dot(vec, vec)); }

  // Private members
private:
  float x_;
  float y_;
};

int main() {
  vec2f A{3, 4};
  vec2f B{2, -1};

  Print(A * 2);
  Print(3 * A);
  std::cout << dot(A, B) << std::endl;
  std::cout << abs(A * 3) << std::endl;

  return 0;
}
