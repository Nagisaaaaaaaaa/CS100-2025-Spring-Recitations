#include <iostream>
#include <memory>
#include <vector>

//? 《OLD GAME!》

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

  //* 假设我们要为 GameObject 和 Tank 实现析构函数，有多少种写法？
  //*
  //* · 对于 GameObject：
  //*   1. ~GameObject() = default;
  //*   2. ~GameObject() { ... }
  //*   3. virtual ~GameObject() = default;
  //*   4. virtual ~GameObject() { ... }
  //*   5. 啥都不写，让编译器自动生成 (等价于第一种情况)。
  //*
  //* · 对于 Tank：
  //*   1. ~Tank() = default;
  //*   2. ~Tank() { ... }
  //*   3. ~Tank() override = default;
  //*   4. ~Tank() override { ... }
  //*   5. 啥都不写，让编译器自动生成 (等价于第一种情况)。
  //*
  //* 竟然有足足 5 * 5 == 25 种情况……
  //* 怎么写嘛！

  //* 别急，有万能公式：
  //* 1. 最远古的父类析构函数必须写 virtual，
  //*    (在我们的例子里，~GameObject 必须用 3 或 4)。
  //* 2. 其他所有的子孙类析构函数，怎么写都无所谓，必定是虚函数，
  //*    (在我们的例子里，~Tank 随便写)。

  return 0;
}
