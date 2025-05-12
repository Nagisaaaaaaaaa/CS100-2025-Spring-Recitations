#include <iostream>
#include <memory>
#include <vector>

//? 《OLD GAME!》

class GameObject {
public:
  virtual void Update() = 0;
};

class Tank : public GameObject {
public:
  void Update() override { std::cout << "Tank::Update" << std::endl; }
};

class Bullet : public GameObject {
public:
  void Update() override { std::cout << "Bullet::Update" << std::endl; }
};

int main() {
  // 实际上很多时候，虚函数会配合智能指针一起使用。
  std::vector<std::unique_ptr<GameObject>> gameObjects;

  gameObjects.push_back(std::make_unique<Tank>());
  gameObjects.push_back(std::make_unique<Bullet>());

  for (auto &gameObject : gameObjects)
    gameObject->Update();

  return 0;
}
