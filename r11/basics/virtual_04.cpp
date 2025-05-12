#include <iostream>

//? 《OLD GAME!》

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
  //! 但是我们不小心忘记为 Bullet 实现 Update 了。
};

int main() {
  Bullet bullet;

  Bullet *bulletPtr = &bullet;
  GameObject *gameObjectPtr = &bullet;

  //! 那我问你，这两行代码会打印出什么？
  bulletPtr->Update();
  gameObjectPtr->Update();

  // 我们忘记实现了一个重要函数，但是竟然没有任何 compile error。
  // 为什么这里不会有 compile error 呢：
  //  1. 我们在父类 GameObject 中，定义了 Update 的“默认行为”。
  //  2. 既然存在默认行为，那么子类 Bullet 就有选择“默认行为”的权力。
  //! 3. 或者说，如果我们想要 要求 Bullet 必须手动定义自己的 Update，
  //!    那就不应该定义“默认行为”。

  return 0;
}
