#include <iostream>
#include <vector>

//? 《OLD GAME!》

// 我们的目标是：
//! 使用父类的指针，调用子类的函数。
// 实际上只需要加上两个关键字就能做到。

class GameObject {
public:
  //! 在这一行，加一个 virtual。
  virtual void Update() { std::cout << "GameObject::Update" << std::endl; }
};

class Tank : public GameObject {
public:
  //! 在这一行，加一个 override。
  void Update() override { std::cout << "Tank::Update" << std::endl; }
};

int main() {
  Tank tank;

  Tank *tankPtr = &tank;
  GameObject *gameObjectPtr = &tank;

  std::vector<GameObject *> gameObjects;
  for (auto *gameObject : gameObjects)
    gameObject->Update();

  //! 那我问你，这两行代码会打印出什么？
  tankPtr->Update();
  gameObjectPtr->Update();

  // 卧槽，发生了什么？
  //! 1. 对成员函数加上 virtual 和 override 这两个关键字之后，
  //!    就会将它从“普通函数”变成“虚函数” (virtual function)。
  //! 2. 使用父类的指针调用虚函数时，会“优先选择”子类的实现。
  //! 3. “优先选择”意味着，如果子类没有实现这个函数，则会调用父类的实现。

  return 0;
}
