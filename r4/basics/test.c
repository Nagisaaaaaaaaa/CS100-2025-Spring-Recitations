#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// int arr[3] = {0, 1, 2};

void print_arr_global(size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void print_arr(int *arr, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(void) {
  int arr[2] = {10, 20};
  print_arr_global(3);
  print_arr(arr, 2);

  return 0;
}
