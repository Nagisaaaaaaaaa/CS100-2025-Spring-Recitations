#include <stdio.h>

int main(void) {
  int imageWidth = 256, imageHeight = 256;

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
