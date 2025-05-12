#include <iostream>
#include <vector>

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

  return 0;
}
