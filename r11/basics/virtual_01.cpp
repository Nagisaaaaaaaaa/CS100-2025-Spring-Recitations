#include <iostream>
#include <vector>

//? 《OLD GAME!》

// 假设我们想使用 C++ 来实现 HW4 坦克大战，
// 我们已经逐渐了解了什么是面向对象编程。

// GameObject 是场景中所有“游戏对象”类型的父类。
// 场景中所有的 GameObject 在每一帧都会
// 调用一次函数 Update，来更新自己的状态。

// Tank   的 Update 负责处理 移动、碰撞、射击……
// Bullet 的 Update 负责处理 移动、碰撞、破坏……

class GameObject {
public:
  // 我们为 Update 定义了默认行为。
  void Update() { std::cout << "GameObject::Update" << std::endl; }
};

class Tank : public GameObject {
public:
  // 我们为 Tank 量身定制了 Update，覆盖掉默认行为。
  void Update() { std::cout << "Tank::Update" << std::endl; }
};

int main() {
  Tank tank;

  // C++ 允许父类的指针指向子类的实例，我们可以这么写代码。
  Tank *tankPtr = &tank;
  GameObject *gameObjectPtr = &tank;

  // 于是，我们自然地希望做游戏开发时，代码长这样：
  // 1. 用一个 std::vector 存储所有游戏对象的指针。
  // 2. 每一帧，遍历所有游戏对象，调用它们的 Update。
  std::vector<GameObject *> gameObjects;
  for (auto *gameObject : gameObjects)
    gameObject->Update();

  // 也就是说，我们希望能够：
  //! 使用父类的指针，调用子类的函数。

  //! 那我问你，这两行代码会打印出什么？
  tankPtr->Update();
  gameObjectPtr->Update();

  return 0;
}
