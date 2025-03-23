#include <stdio.h>

/// \brief Transform the given array `arr` with an operator `op`.
typedef struct {
  int *arr;
  int (*op)(int);
} Transform;

/// \brief Evaluate the transformed value of `trans` at index `i`.
int Eval(Transform trans, size_t i) {
  return trans.op(trans.arr[i]);
}

int Squared(int v) {
  return v * v;
}

int Negative(int v) {
  return -v;
}

#define cN ((size_t)5)

int main(void) {
  int arr[cN];
  for (size_t i = 0; i < cN; ++i)
    arr[i] = i;

  Transform squared = {arr, Squared};
  Transform negative = {arr, Negative};

  for (size_t i = 0; i < cN; ++i)
    printf("%d\n", Eval(squared, i));

  for (size_t i = 0; i < cN; ++i)
    printf("%d\n", Eval(negative, i));

  return 0;
}
