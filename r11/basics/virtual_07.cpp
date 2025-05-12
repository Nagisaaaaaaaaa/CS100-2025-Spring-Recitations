#include <iostream>
#include <memory>
#include <vector>

//? 《OLD GAME!》

// 现在，我们让事情变得更复杂一点。
// 假设这 3 个 class 都显式地实现了析构函数。

class GameObject {
public:
  ~GameObject() { std::cout << "GameObject::~GameObject" << std::endl; }
};

class Tank : public GameObject {
public:
  ~Tank() { std::cout << "Tank::~Tank" << std::endl; }
};

class Bullet : public GameObject {
public:
  ~Bullet() { std::cout << "Bullet::~Bullet" << std::endl; }
};

int main() {
  std::vector<std::unique_ptr<GameObject>> gameObjects;

  gameObjects.push_back(std::make_unique<Tank>());
  gameObjects.push_back(std::make_unique<Bullet>());

  //! 那我问你，析构的时候会打印出什么？

  //! 答案：
  //!   永远只会调用父类 GameObject 的析构函数，
  //!   因为所有的 std::unique_ptr 的类型都是 GameObject。
  //!   换成裸指针，显式地调用 delete，结果也是一样的。

  //! 难道说，当涉及到继承的时候，
  //! 析构函数必须是虚函数吗？

  return 0;
}
