/*

  ! Baseline:
  ! 1. Why reference? Why not pointer?

*/

struct Vec3 {
  int v[3];
};

struct Vec30 {
  int v[30];
};

Vec3 AddByValue(Vec3 a, Vec3 b) {
  // ...
}

Vec30 AddByValue(Vec30 a, Vec30 b) {
  // ...
}

Vec30 AddByPointer(const Vec30 *a, const Vec30 *b) {
  // ...
}

Vec30 AddByReference(const Vec30 &a, const Vec30 &b) {
  // ...
}
