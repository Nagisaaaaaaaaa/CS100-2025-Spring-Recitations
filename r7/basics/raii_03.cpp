#include <vector>

int main() {
  //! `vec` owns the array.
  std::vector<int> vec(5);

  //! `data` does not own the array.
  int *data = vec.data();
}
