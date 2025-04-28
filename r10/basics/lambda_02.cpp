/*

 ! Baseline:
 ! 1. Understand the following example

*/

#include <iostream>

//* 千早爱音同学回家后，为了拯救自己的乐队
//* 仔细阅读了cppreference
//* 发现了关于mutable关键词的介绍：
//* 上面写道：allow assignment to a variable captured by copy in a non-mutable lambda
//* 她于是试图这样改上面那段代码
int main() {
  using namespace std;
  string band{"CRYCHIC"};
  string after;

  auto lamb = [band]() mutable {
    band += "!"; //* 爱音：这次我一个个加感叹号
    return band;
  };

  after = lamb(); //* 爱音：先拿CRYCHIC试试水
  cout << band << endl;
  cout << after << endl;

  //* 嘻嘻，这次一定能成了
  band = "MyGO";
  after = lamb();
  after = lamb();
  after = lamb();
  after = lamb();
  after = lamb();
  cout << band << endl;
  cout << after << endl;

  //! 爱音同学受不了了，决定跟助教爆了
}
