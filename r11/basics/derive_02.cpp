#include <iostream>

// struct that represent a shooting ray
struct Ray {
  // ... some implementation
};

// 实际上写法的思路是这样的：
// 通过继承，让每个类里面的内容都足够地 `必要且清爽`

class Material {
public:
  virtual ~Material() = default;

public:
  virtual Ray generateOutRay(Ray input_ray) const { /*...*/ }
};

class Lambertian : public Material {
public:
  Lambertian(double albedo)
      : albedo_(albedo) {}

public:
  Ray generateOutRay(Ray input_ray) const override {
    // Real implementation here!
  }

private:
  double albedo_;
};

class Metal : public Material {
public:
  Metal(double albedo, double fuzz)
      : albedo_(albedo)
      , fuzziness_(fuzz) {}

public:
  Ray generateOutRay(Ray input_ray) const override {
    // Real implementation here!
  }

private:
  double albedo_;
  double fuzziness_;
};

// ... other mateterals
