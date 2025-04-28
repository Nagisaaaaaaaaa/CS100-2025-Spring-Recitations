/*

 ! Baseline:
 ! 1. Understand the following example

*/

#include <iostream>

//* 助教安慰说：你先别急，看我略施小计
int main() {
  using namespace std;
  string band{"CRYCHIC"};
  string after;

  auto lamb = [&band]() mutable { return band + "!!!!!"; };

  after = lamb();
  cout << band << endl;
  cout << after << endl;

  band = "MyGO";
  after = lamb();
  cout << band << endl;
  cout << after << endl;
}

//* 爱音同学很高兴，但是不解：为什么会这样？
//* 答案藏在这段说明当中：
//* For each lambda object, the capture happens at the time the lambda object is created
//* — and each lambda object keeps its own copy (or reference) of the captured variables.
//* Thus, the capture is executed once at construction, not every time the lambda is called.
