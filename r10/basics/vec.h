#include <cmath>
#include <iostream>
#include <ostream>
#include <string>

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
  float &x() { return x_; }

  float &y() { return y_; }

  float x() const { return x_; }

  float y() const { return y_; }

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

  // Scalar * overloading (s * vec)
  friend vec2f operator*(float s, const vec2f &vec) { return vec * s; }

  // Binray dot
  friend float dot(const vec2f &alice, const vec2f &bob) { return (alice.x_ * bob.x_) + (alice.y_ * bob.y_); }

  // ostream operator
  friend std::ostream &operator<<(std::ostream &os, const vec2f &vec) { return os << to_string(vec); }

  // Public Utils
public:
  friend void Print(const vec2f &vec) { std::cout << "{ " << vec.x_ << ", " << vec.y_ << " }" << std::endl; }

  friend float abs(const vec2f &vec) { return sqrtf(dot(vec, vec)); }

  friend std::string to_string(const vec2f &vec) {
    using std::to_string;
    return "{ " + to_string(vec.x_) + ", " + to_string(vec.y_) + " }";
  }

  // Private members
private:
  float x_;
  float y_;
};
