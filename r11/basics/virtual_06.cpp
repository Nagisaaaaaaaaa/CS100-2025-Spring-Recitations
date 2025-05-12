#include <iostream>
#include <memory>
#include <vector>

//? 《OLD GAME!》

class GameObject {
public:
  virtual void Update() { std::cout << "GameObject::Update" << std::endl; }
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
  // 至此，我们已经学会如何
  //! 使用父类的指针，调用子类的函数。
  // 既然这个环节必须用到指针，就不得不提智能指针。

  // 实际上很多时候，虚函数会配合智能指针一起使用。
  std::vector<std::unique_ptr<GameObject>> gameObjects;

  gameObjects.push_back(std::make_unique<Tank>());
  gameObjects.push_back(std::make_unique<Bullet>());

  //! 那我问你，这两行代码会打印出什么？
  for (auto &gameObject : gameObjects)
    gameObject->Update();

  return 0;
}
