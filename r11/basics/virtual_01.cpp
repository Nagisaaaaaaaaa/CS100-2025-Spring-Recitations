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

  Tank *tankPtr = &tank;
  GameObject *gameObjectPtr = &tank;

  //! 那我问你，这两行代码会打印出什么？
  tankPtr->Update();
  gameObjectPtr->Update();

  // 这不是我们想要的，因为假设我们在设计一个游戏引擎，
  // 肯定希望这么写代码：
  std::vector<GameObject *> gameObjects;
  for (auto *gameObject : gameObjects)
    gameObject->Update(); // 永远只会调用父类的 Update 啊。

  // 更具体地说，我们希望能够：
  //! 使用父类的指针，调用子类的函数。

  return 0;
}
