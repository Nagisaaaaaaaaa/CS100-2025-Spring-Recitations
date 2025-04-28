/*

 ! Baseline:
 ! 1. Understand the following example

*/

#include <iostream>

//* This was a good example from stackoverflow.
//* 千早爱音同学希望，在自己的乐队名字后面加五个感叹号
//* 暗示乐队由五个 `好姐妹` 组成
//* 她刚在CS100上学习了lambda的基础，于是她随手写了这样一个函数：
int main() {
  using namespace std;
  string band{"CRYCHIC"};
  string after;

  auto lamb = [band]() { return band + "!!!!!"; };

  after = lamb();
  cout << band << endl;
  cout << after << endl;

  band = "MyGO";
  after = lamb();
  cout << band << endl;
  cout << after << endl;

  //! 千早爱音同学觉得细思极恐！
}
