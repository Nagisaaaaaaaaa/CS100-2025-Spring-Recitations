#include <iostream>
#include <vector>

//? 《OLD GAME!》

class GameObject {
public:
  // 在这一行，加一个 virtual。
  virtual void Update() { std::cout << "GameObject::Update" << std::endl; }
};

class Tank : public GameObject {
public:
  // 在这一行，加一个 override。
  void Update() override { std::cout << "Tank::Update" << std::endl; }
};

int main() {
  Tank tank;

  // 如果把 pointer 换成 reference 会发生什么？
  Tank &tankRef = tank;
  GameObject &gameObjectRef = tank;

  //! 那我问你，这两行代码会打印出什么？
  tankRef.Update();
  gameObjectRef.Update();

  //* 尽管 reference 也能够很好地运作，
  //* 但实际工程上，大家都会选择使用 pointer。
  //* 为什么呢？看看这个例子。
  std::vector<GameObject &> gameObjects;
  for (auto &gameObject : gameObjects)
    gameObject.Update();

  //* std::vector 可以存 pointer 但不能存 reference！
  //* 这是个所有权 (ownership) 方面的哲学问题。
  //*
  //* 如果 std::vector 允许存 reference，
  //* 那么谁才是真正的所有者呢？一切都会很混乱。

  //! 总结：
  //!   当涉及到继承、虚函数的时候，
  //!   请永远选择用 pointer 而不是 reference。

  return 0;
}
