/*

  ! Baseline:
  ! 1. Who owns the array in this example?
  ! 2. Why?

*/

#include <vector>

int main() {
  //! `vec` owns the array.
  std::vector<int> vec(5);

  //! `data` does not own the array.
  int *data = vec.data();

  return 0;
}
