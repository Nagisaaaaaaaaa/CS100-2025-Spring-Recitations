#include <iostream>
#include <memory>
#include <vector>

class GameObject {
public:
  virtual ~GameObject() { std::cout << "GameObject::~GameObject" << std::endl; }

public:
  virtual void Update() = 0;
};

class Tank : public GameObject {
public:
  ~Tank() override { std::cout << "Tank::~Tank" << std::endl; }

public:
  void Update() override { std::cout << "Tank::Update" << std::endl; }
};

class Bullet : public GameObject {
public:
  ~Bullet() override { std::cout << "Bullet::~Bullet" << std::endl; }

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
  //!   子类和父类的析构函数都会被调用。
  //! 因为：
  //! 1. 因为析构函数是虚函数，所以即使指针的类型是 GameObject，
  //!    也会调用子类的析构函数。
  //! 2. 子类的析构函数会自动调用父类的析构函数，
  //!    顺序是：先子类、后父类，
  //!    与构造函数的顺序正好相反。

  return 0;
}
