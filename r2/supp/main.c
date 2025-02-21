#include <stdbool.h>
#include <stdio.h>

/// \brief Compute the squared norm of a vector `(x, y)`.
double SquaredNorm(double x, double y) {
  return x * x + y * y;
}

/// \brief Determine whether coordinate `(i, j)` is inside the ellipse, which is
/// centered at `(centerX, centerY)` and has radius `(radiusX, radiusY)`.
bool IsInEllipse(int i, int j, double centerX, double centerY, double radiusX, double radiusY) {
  // Compute center of the pixel `(i, j)`.
  double x = (double)i + 0.5;
  double y = (double)j + 0.5;

  double dirX = (x - centerX) / radiusX;
  double dirY = (y - centerY) / radiusY;
  return SquaredNorm(dirX, dirY) <= 1.0;
}

/// \brief Determine whether coordinate `(i, j)` is inside the sphere, which is
/// centered at `(centerX, centerY)` and has radius `radius`.
///
/// \details You may wonder why not implement `IsInSphere` based on `IsInEllipse`.
/// That is because multiplications are usually faster than divisions for floating points.
bool IsInSphere(int i, int j, double centerX, double centerY, double radius) {
  // Compute center of the pixel `(i, j)`.
  double x = (double)i + 0.5;
  double y = (double)j + 0.5;

  double dirX = x - centerX;
  double dirY = y - centerY;
  return SquaredNorm(dirX, dirY) <= radius * radius;
}

/// \brief Determine whether coordinate `(i, j)` is inside the rectangle, whose
/// range is from `(minX, minY)` to `(maxX, maxY)`.
bool IsInRectangle(int i, int j, double minX, double minY, double maxX, double maxY) {
  // Compute center of the pixel `(i, j)`.
  double x = (double)i + 0.5;
  double y = (double)j + 0.5;

  return x >= minX && x <= maxX && y >= minY && y <= maxY;
}

//
//
//
int main(void) {
  int imageWidth = 256, imageHeight = 256;

  printf("P3\n%d %d\n255\n", imageWidth, imageHeight);

  for (int j = 0; j < imageHeight; ++j) {
    for (int i = 0; i < imageWidth; ++i) {
      // Default values.
      double r = 1.0, g = 1.0, b = 1.0;

      double quarterX = (double)imageWidth / 4.0;
      double quarterY = (double)imageHeight / 4.0;

      if (IsInEllipse(i, j, quarterX * 3.5, quarterY * 2.00, quarterX * 0.5, quarterY * 2.00))
        r = 0.75, g = 0.25, b = 1.00;
      if (IsInEllipse(i, j, quarterX * 3.0, quarterY * 2.25, quarterX * 0.5, quarterY * 1.75))
        r = 0.25, g = 0.25, b = 1.00;
      if (IsInEllipse(i, j, quarterX * 2.5, quarterY * 2.50, quarterX * 0.5, quarterY * 1.50))
        r = 0.25, g = 1.00, b = 1.00;
      if (IsInEllipse(i, j, quarterX * 2.0, quarterY * 2.75, quarterX * 0.5, quarterY * 1.25))
        r = 0.25, g = 1.00, b = 0.25;
      if (IsInEllipse(i, j, quarterX * 1.5, quarterY * 3.00, quarterX * 0.5, quarterY * 1.00))
        r = 1.00, g = 1.00, b = 0.25;
      if (IsInEllipse(i, j, quarterX * 1.0, quarterY * 3.25, quarterX * 0.5, quarterY * 0.75))
        r = 1.00, g = 0.75, b = 0.25;
      if (IsInEllipse(i, j, quarterX * 0.5, quarterY * 3.50, quarterX * 0.5, quarterY * 0.50))
        r = 1.00, g = 0.25, b = 0.25;

      // [0.0, 1.0] -> [0, 255].
      int ir = (int)(255.0 * r);
      int ig = (int)(255.0 * g);
      int ib = (int)(255.0 * b);

      printf("%d %d %d\n", ir, ig, ib);
    }
  }

  return 0;
}
