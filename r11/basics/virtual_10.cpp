#include <iostream>

//? 《OLD GAME!》

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
  // 于是，对于 gameObjectPtr，
  // 我们实际上拥有 3 种调用 Update 的写法。

  // (1). 虚函数。
  gameObjectPtr->UpdateVirtual();

  // (2). 如果我们事先就知道指向的是个 Tank，
  //      就可以调用 static_cast 转换到子类指针。
  //      然后调用非虚函数的版本。
  {
    Tank *ptr = static_cast<Tank *>(gameObjectPtr);
    ptr->UpdateNonVirtual();
  }

  // (3). 我觉得虚函数让我的生活过得太轻松了，
  //      我想体验一下没有虚函数的日子。
  {
    Tank *ptr = dynamic_cast<Tank *>(gameObjectPtr);
    if (ptr)
      ptr->UpdateNonVirtual();
    else
      gameObjectPtr->UpdateNonVirtual();
  }

  //! 如何选择使用哪一种写法呢？
  //!
  //! 结论：
  //! 1. 性能：(2) > (1) > (3)。
  //! 2. 某些情况下，(2) 的性能会远大于 (1) 和 (3)。
  //! 3. 请永远不要使用 (3)。

  return 0;
}
