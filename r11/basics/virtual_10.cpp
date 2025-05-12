#include <iostream>

class GameObject {
public:
  void UpdateNonVirtual() { std::cout << "GameObject::Update" << std::endl; }

  virtual void UpdateVirtual() { std::cout << "GameObject::Update" << std::endl; }
};

class Tank : public GameObject {
public:
  void UpdateNonVirtual() { std::cout << "Tank::Update" << std::endl; }

  void UpdateVirtual() override { std::cout << "Tank::Update" << std::endl; }
};

int main() {
  Tank tank;
  GameObject *gameObjectPtr = &tank;

  // 我们知道 static_cast 和 dynamic_cast 可以
  // 在父类、子类的指针之间做类型转换。
  // 于是，我们实际上拥有 3 种写法。

  // (1). 通过虚函数来选择调用哪个函数。
  gameObjectPtr->UpdateVirtual();

  // (2). 假设我们事先知道指向的是个 Tank，
  //      就可以调用 static_cast 转换到子类指针。
  //      然后调用非虚函数的版本。
  {
    Tank *ptr = static_cast<Tank *>(gameObjectPtr);
    ptr->UpdateNonVirtual();
  }

  // (3). 欸，我就不喜欢虚函数，就喜欢 dynamic_cast。
  {
    Tank *ptr = dynamic_cast<Tank *>(gameObjectPtr);
    if (ptr)
      ptr->UpdateNonVirtual();
    else
      gameObjectPtr->UpdateNonVirtual();
  }

  //! 结论：
  //! 1. 性能：(2) > (1) > (3)。
  //! 2. 某些情况下，(2) 的性能会远大于 (1) 和 (3)。
  //! 3. 请永远不要使用 (3) 这种写法。

  return 0;
}
