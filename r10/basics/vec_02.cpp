#include <iostream>

//! 一个很自然的需求是，我们希望我们的向量类型能够直接以
//! A + B 而不是 Add(A, B) 这种形式来进行
//! 所以我们需要 `重载` 运算符来实现这件事
//! 这个文件中，我们先来解决加减

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

  //! 思考这样一个问题，为什么二元运算符 `+` `-` 我们都用 friend + non-member
  //! 而一元运算符 `-` 我们采用member呢？

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

  Print(A + B);
  Print(-A);
  Print(A - B);

  return 0;
}
