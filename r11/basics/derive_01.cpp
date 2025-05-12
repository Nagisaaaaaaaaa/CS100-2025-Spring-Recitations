#include <iostream>

// struct that represent a shooting ray
struct Ray {
  // ... some implementation
};

// 在渲染器中：
// 如果不采用继承，我们可能会怎样处理不同的材质？
// 这种处理方式糟糕在哪里？

class Material {
public:
  // CTORs

public:
  Ray generateOutRay(Ray input_ray) const {
    switch (this->mat_type_) {
    case Material_Type::METAL:
      // Generate output ray in a "metalic" way
      break;
    case Material_Type::LAMBERTIAN:
      // Generate output ray in a "lambertian" way
      break;

    // ... Other materials
    default:
      break;
    }
  }

private:
  enum class Material_Type { METAL, LAMBERTIAN /* ...*/ };

private:
  Material_Type mat_type_;

  // quantities used in dielectic materials
  double refract_index_;
  double reflectance_;

  // quantities used in diffusive materials & metals
  double albedo_;

  // quantities used in metals
  double fuzziness_;
};

// 我们分析一下矛盾的根源：
// 之所以这些形形色色的材质能被统一成一个类 `Material`，
// 是因为他们拥有本质性的 `相同` ，即：
// 拥有一个行为（接口），例如接受一条光线，进行某种【计算】，返回另一条光线
// 但同时，【计算】的过程确又需要 `不同` 的原材料（成员变量）和方法（成员函数）
// 比如说我们可以回顾一下课上 `discounted items` 或者 `animal sound` 的经典例子

//! 正是这对 `相同` 与 `不同` 的矛盾，造成了上面那种写法的违和感和不方便

// 所以如果说，class存在的意义是将不同的东西统一起来，形成公用的接口
// 那么derivation存在的意义，恰恰就是为这 `相同` 接口下的 `不同实现`
// 做出必要的妥协。通过让父类Base来扮演一个 `最大公约数` 的角色，最大程度地
// 减少代码冗余，同时又为五花八门地具体实现提供了自由度，方便程序员 `因材施教`。
