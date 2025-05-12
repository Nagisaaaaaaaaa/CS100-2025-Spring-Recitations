#include <iostream>

//? 《OLD GAME!》

class GameObject {
public:
  //! 这次我们不提供“默认行为”了。
  // virtual void Update() { std::cout << "GameObject::Update" << std::endl; }
  virtual void Update() = 0;
};

class Tank : public GameObject {
public:
  void Update() override { std::cout << "Tank::Update" << std::endl; }
};

class Bullet : public GameObject {
public:
  //! 如果不存在“默认行为”，
  //! 不小心忘记实现 Update 就会导致 compile error。
};

int main() {
  //! 会直接在这里 compile error。
  Bullet bullet;

  Bullet *bulletPtr = &bullet;
  GameObject *gameObjectPtr = &bullet;

  bulletPtr->Update();
  gameObjectPtr->Update();

  //! 我们称 Update 这样的函数为“纯虚函数” (pure virtual function)。
  //! 这里 pure 指的就是没有“默认行为”。

  //! 纯虚函数的意义：
  //!   我们永远无法实例化一个 class，
  //!   直到我们实现了所有的纯虚函数。
  GameObject v0; // 无法实例化，因为没有实现“纯虚函数” Update。
  Tank v1;       // 可以实例化，因为已经实现了所有“纯虚函数”。
  Bullet v2;     // 无法实例化，因为没有实现“纯虚函数” Update。

  //! 我们称存在未实现“纯虚函数”的 class 为 abstract class。
  // GameObject 是 abstract class。
  // Tank       不是 abstract class。
  // Bullet     是 abstract class。

  return 0;
}
