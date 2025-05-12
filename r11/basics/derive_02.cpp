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

// 从现在开始，同学们已经进入了 `设计模式` 的领域
// 工厂模式 / 策略模式 / 监听模式 ... 等许多抽象、复杂但是有趣的思想等待着大家
// 而它们中很大一部分都依赖于 `运行时多态`，往往也就是继承
// 这些内容CS100只会涵盖相当有限的部分（例如lecture22中那样浅尝辄止的讨论）
// 感兴趣的同学可以去阅读课程的推荐数目（我们群里也转载过）
