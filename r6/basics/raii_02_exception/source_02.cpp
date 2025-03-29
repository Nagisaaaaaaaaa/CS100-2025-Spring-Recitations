/*

  ! Baseline:
  ! 1. 所谓的“半死”，意思是，既可以选择“原地结束”，也可以选择“起死回生”。
  !   1.1. “原地结束”：不需要多写一行代码，
  !                   出现异常时，程序直接终止。
  !   1.2. “起死回生”：需要加一层 `try-catch`，
  !                   出现异常时，死在 `try` 里面，复活在 `catch` 里面。

  * Bonus:

*/

#include <iostream>
#include <vector>

int main() {
  try {

    std::cout << "Start allocating" << std::endl;

    std::vector<int> v(0xFFFFFFFFFFFFFFFLLU);

    std::cout << "Finished allocating" << std::endl;

  } catch (std::exception &e) { //
    // This line prints the exception message.
    std::cout << "The exception message is: " << e.what() << std::endl;
  }

  std::cout << "All done" << std::endl;

  return 0;
}
