#include <iostream>
#include <vector>

//? 《OLD GAME!》

class GameObject {
public:
  // 在这一行，加一个 virtual。
  virtual void Update() { std::cout << "GameObject::Update" << std::endl; }
};

class Tank : public GameObject {
public:
  // 在这一行，加一个 override。
  void Update() override { std::cout << "Tank::Update" << std::endl; }
};

int main() {
  Tank tank;

  Tank *tankPtr = &tank;
  GameObject *gameObjectPtr = &tank;

  //! 那我问你，这两行代码会打印出什么？
  tankPtr->Update();
  gameObjectPtr->Update();

  std::vector<GameObject *> gameObjects;
  for (auto *gameObject : gameObjects)
    gameObject->Update();

  // 感受一下我们做到了什么？
  //!   使用父类的指针，调用子类的函数。
  //! 我们称 Update 这样的函数为“虚函数” (virtual)。

  return 0;
}
