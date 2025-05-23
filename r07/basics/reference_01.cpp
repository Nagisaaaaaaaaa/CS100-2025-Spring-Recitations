/*

  ! Baseline:
  ! 1. Pass by value, by pointer, or by reference?
  ! 2. Why reference? Why not pointer?

*/

struct Vec3 {
  int v[3];
};

struct Vec30 {
  int v[30];
};

Vec3 Add_PassByValue(Vec3 a, Vec3 b) {
  // ...
}

Vec30 Add_PassByValue(Vec30 a, Vec30 b) {
  // ...
}

Vec30 Add_PassByPointer(const Vec30 *a, const Vec30 *b) {
  // ...
}

Vec30 Add_PassByReference(const Vec30 &a, const Vec30 &b) {
  // ...
}

int main() {
  Vec30 a, b;

  Vec30 c = Add_PassByPointer(&a, &b);
  //   Vec30 c = Add_PassByReference(a, b);

  return 0;
}
