#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define Min(a, b) (((a) < (b)) ? (a) : (b))

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
  int fps = atoi(argv[2]);
  double time = (double)frame / (double)fps;

  int imageWidth = 256, imageHeight = 256;

  int nPoints = 1 + (int)(time / 0.1);

  double *posX = malloc(nPoints * sizeof(double));
  double *posY = malloc(nPoints * sizeof(double));
  for (int i = 0; i < nPoints; ++i) {
    posX[i] = imageWidth * 0.01 * i;
    posY[i] = imageHeight * 0.45 * sin(time - i * 0.1) + imageHeight * 0.5;
  }

  double radius = (double)Min(imageWidth, imageHeight) * 0.01;

  printf("P3\n%d %d\n255\n", imageWidth, imageHeight);

  for (int j = 0; j < imageHeight; ++j) {
    for (int i = 0; i < imageWidth; ++i) {
      // Default values.
      double r = 1.0, g = 1.0, b = 1.0;

      for (int iPoints = 0; iPoints < nPoints; ++iPoints)
        if (IsInCircle(i, j, posX[iPoints], posY[iPoints], radius))
          r = 0.0, g = 0.0, b = 0.0;

      // [0.0, 1.0] -> [0, 255].
      int ir = (int)(255.0 * r);
      int ig = (int)(255.0 * g);
      int ib = (int)(255.0 * b);

      printf("%d %d %d\n", ir, ig, ib);
    }
  }

  free(posX);
  free(posY);

  return 0;
}
