/*

  This piece of source code corresponds to:
  Recitaion 06 - Struct.

  ! Baseline:
  ! 1. Understand the following examples.
  ! 2. Caution: memory alignment.

*/

#include <stddef.h>
#include <stdio.h>

enum Type { INT, FLOAT, STRING };

typedef struct {

  enum Type type; // 4 Bytes

  union {
    int i;
    float f;
    char str[4];
  } data;
} Variant;

typedef union {
  int i;
  float f;
  char str[5];
} MyUnion;

void printVariant(Variant v) {
  switch (v.type) {
  case INT:
    printf("Integer: %d\n", v.data.i);
    break;
  case FLOAT:
    printf("Float: %f\n", v.data.f);
    break;
  case STRING:
    printf("String: %s\n", v.data.str);
    break;
  }
}

int main() {

  printf("Size of Variant = %d Bytes.\n", (int)sizeof(Variant));
  printf("Size of MyUnion = %d Bytes.\n", (int)sizeof(MyUnion));

  Variant v1 = {INT, .data.i = 42};
  Variant v2 = {FLOAT, .data.f = 3.14F};
  Variant v3 = {STRING, .data.str = "^.^"};
  Variant varlist[3] = {v1, v2, v3};

  for (size_t iv = 0; iv < 3; ++iv) {
    printVariant(varlist[iv]);
  }

  return 0;
}
