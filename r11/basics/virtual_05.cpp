#include <iostream>

class GameObject {
public:
  //! 不提供“默认行为”的版本：
  // virtual void Update() { std::cout << "GameObject::Update" << std::endl; }
  virtual void Update() = 0;
};

class Tank : public GameObject {
public:
  void Update() override { std::cout << "Tank::Update" << std::endl; }
};

// 除了 Tank 之外，我们还需要 Bullet 之类的 GameObject。
class Bullet : public GameObject {
public:
  // 但是我不小心忘记实现 Bullet 的 Update 了。
  //! 这时候，不小心忘记实现 Update 就会触发 compile error。
};

int main() {
  Bullet bullet;

  Bullet *bulletPtr = &bullet;
  GameObject *gameObjectPtr = &bullet;

  bulletPtr->Update();
  gameObjectPtr->Update();

  //! 我们称 Update 这样的函数为“纯虚函数” (pure virtual)。

  return 0;
}
