#include <glm/glm.hpp>
#include <iostream>

using namespace glm;

int main() {
  vec3 a(1, 0, 0);
  vec3 b(0, 1, 0);
  vec3 c = cross(a, b);

  printf("c = (%f, %f, %f)\n", c.x, c.y, c.z);
}
