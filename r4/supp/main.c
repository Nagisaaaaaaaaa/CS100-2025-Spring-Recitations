#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/// \brief Compute the squared norm of a vector `(x, y)`.
double SquaredNorm(double x, double y) {
  return x * x + y * y;
}

/// \brief Determine whether coordinate `(i, j)` is inside the circle, which is
/// centered at `(centerX, centerY)` and has radius `radius`.
///
/// \details You may wonder why not implement `IsInCircle` based on `IsInEllipse`.
/// That is because multiplications are usually faster than divisions for floating points.
bool IsInCircle(int i, int j, double centerX, double centerY, double radius) {
  // Compute center of the pixel `(i, j)`.
  double x = (double)i + 0.5;
  double y = (double)j + 0.5;

  double dirX = x - centerX;
  double dirY = y - centerY;
  return SquaredNorm(dirX, dirY) <= radius * radius;
}

//
//
//
int main(int argc, char **argv) {
  int frame = atoi(argv[1]);

  int imageWidth = 128, imageHeight = 128;

  printf("P3\n%d %d\n255\n", imageWidth, imageHeight);

  for (int j = 0; j < imageHeight; ++j) {
    for (int i = 0; i < imageWidth; ++i) {
      // r: [0, w - 1] -> [0.0, 1.0].
      // g: [0, h - 1] -> [0.0, 1.0].
      double r = (double)i / (double)(imageWidth - 1);  // `r` = red.
      double g = (double)j / (double)(imageHeight - 1); // `g` = green.
      double b = 0.25;                                  // `b` = blue.

      // [0.0, 1.0] -> [0, 255].
      int ir = (int)(255.0 * r);
      int ig = (int)(255.0 * g);
      int ib = (int)(255.0 * b);

      printf("%d %d %d\n", ir, ig, ib);
    }
  }

  return 0;
}
