#include <Arietta/Stateful/Vector.hpp>

struct Another {};

int main() {
  using namespace arietta;
  using namespace arietta::stateful;

  Vector<>::PushBack<int>();
  Vector<>::PushBack<size_t>();
  static_assert(std::is_same_v<Vector<>::At<0>, int>);
  static_assert(std::is_same_v<Vector<>::At<1>, size_t>);
  static_assert(Vector<>::Size() == 2);

  Vector<Another>::PushBack<float>();
  Vector<Another>::PushBack<double>();
  static_assert(std::is_same_v<Vector<Another>::At<0>, float>);
  static_assert(std::is_same_v<Vector<Another>::At<1>, double>);
  static_assert(Vector<Another>::Size() == 2);

  return 0;
}
