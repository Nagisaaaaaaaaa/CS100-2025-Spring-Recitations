/*

  ! Baseline:
  ! 1. Understand the basic rules of namespace.
  ! 2. Understand the nested structure of namespace.

*/

namespace ShanghaiTech {

namespace SIST {

namespace CS100 {

class Recitation {
public:
  Recitation() = default;
  ~Recitation() = default;
};

Recitation random_rclass() {
  return {};
}

} // namespace CS100

namespace CS252 {
// ... cousin namespace
} // namespace CS252

} // namespace SIST

class Student {
public:
  SIST::CS100::Recitation recitation_class;
  Student() = default;
  ~Student() = default;
};

Student give_me_a_student() {
  return {};
}
} // namespace ShanghaiTech
