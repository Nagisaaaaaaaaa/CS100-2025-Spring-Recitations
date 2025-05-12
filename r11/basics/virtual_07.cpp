#include <iostream>
#include <memory>
#include <vector>

//? 《OLD GAME!》

// 现在，我们让事情变得更复杂一点。
// 假设这 3 个 class 都显式地实现了析构函数。

class GameObject {
public:
  ~GameObject() { std::cout << "GameObject::~GameObject" << std::endl; }

public:
  virtual void Update() = 0;
};

class Tank : public GameObject {
public:
  ~Tank() { std::cout << "Tank::~Tank" << std::endl; }

public:
  void Update() override { std::cout << "Tank::Update" << std::endl; }
};

class Bullet : public GameObject {
public:
  ~Bullet() { std::cout << "Bullet::~Bullet" << std::endl; }

public:
  void Update() override { std::cout << "Bullet::Update" << std::endl; }
};

int main() {
  std::vector<std::unique_ptr<GameObject>> gameObjects;

  gameObjects.push_back(std::make_unique<Tank>());
  gameObjects.push_back(std::make_unique<Bullet>());

  for (auto &gameObject : gameObjects)
    gameObject->Update();

  //! 那我问你，析构的时候会打印出什么？

  //! 答案：
  //!   永远只会调用父类 GameObject 的析构函数，
  //!   因为所有的 unique_ptr 的类型都是 GameObject。

  //! 难道说，析构函数必须是 virtual 的吗？

  return 0;
}
