#include <iostream>

class GameObject {
public:
  virtual void Update() { std::cout << "GameObject::Update" << std::endl; }
};

class Tank : public GameObject {
public:
  void Update() override { std::cout << "Tank::Update" << std::endl; }
};

// 除了 Tank 之外，我们还需要 Bullet 之类的 GameObject。
class Bullet : public GameObject {
public:
  // 但是我不小心忘记实现 Bullet 的 Update 了。
};

int main() {
  Bullet bullet;

  Bullet *bulletPtr = &bullet;
  GameObject *gameObjectPtr = &bullet;

  bulletPtr->Update();
  gameObjectPtr->Update();

  // 我们忘记实现了一个重要函数，但是竟然没有任何 compile error。
  // 这实际上是一个设计的哲学问题：
  //  1. 我们在父类 GameObject 中，定义了 Update 的“默认行为”。
  //  2. 既然有默认行为，那么子类 Bullet 也有选择“默认行为”的权力啊。
  //! 3. 如果我们想要要求 Bullet 必须手动定义自己的 Update，
  //!    那就不应该为它提供“默认行为”。

  return 0;
}
