/*

  This piece of source code corresponds to:
  Recitaion Slide 02 - sizeof.

  The result may vary across platforms.
  Don't worry if you don't get the same result.

  ! Baseline takeaway:
  ! 1. sizeof(signed T) = sizeof(unsigned T);
  ! 2. sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long);

*/
#include <stdio.h>

int main(void) {

  printf("Size of <%s> is %d Byte(s).\n", "int", (int)sizeof(int));
  printf("Size of <%s> is %d Byte(s).\n", "unsigned int", (int)sizeof(unsigned int));
  printf("Size of <%s> is %d Byte(s).\n", "short", (int)sizeof(short));
  printf("Size of <%s> is %d Byte(s).\n", "long", (int)sizeof(long));
  printf("Size of <%s> is %d Byte(s).\n", "long long", (int)sizeof(long long));
  printf("Size of <%s> is %d Byte(s).\n", "char", (int)sizeof(char));
  // No "bool" type for C? --> We may force compile with g++ and take a look!
  //   printf("Size of <%s> is %d Byte(s).\n", "bool", (int)sizeof(bool));
  printf("Size of <%s> is %d Byte(s).\n", "float", (int)sizeof(float));
  printf("Size of <%s> is %d Byte(s).\n", "double", (int)sizeof(double));
  printf("Size of <%s> is %d Byte(s).\n", "long double", (int)sizeof(long double));

  return 0;
}
