#include <iostream>
#include <vector>

class GameObject {
public:
  void Update() { std::cout << "GameObject::Update" << std::endl; }
};

class Tank : public GameObject {
public:
  void Update() { std::cout << "Tank::Update" << std::endl; }
};

int main() {
  Tank tank;

  Tank *tankPtr = &tank;
  GameObject *gameObjectPtr = &tank;

  //! 那我问你，这两行代码会打印出什么？
  tankPtr->Update();
  gameObjectPtr->Update();

  // 这不是我们想要的，因为假设我们在设计一个游戏引擎，
  // 肯定希望这么写代码：
  std::vector<GameObject *> gameObjects;
  for (auto *gameObject : gameObjects)
    gameObject->Update(); // 永远只会调用父类的 Update 啊。

  // 更具体地说，我们希望能够：
  //! 使用父类的指针，调用子类的函数。

  return 0;
}
