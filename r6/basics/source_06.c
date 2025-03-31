/*

  This piece of source code corresponds to:
  Recitaion 06 - Struct.

  ! Baseline:
  ! 1. Understand the following examples.
  ! 2. Remember the Bit-Field order. (low -> high)
  * Bonus:
  * 3. Rewrite your HW2-Problem3 solution with this technique.

*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef uint16_t u16;

typedef union {
  u16 codeVal; // 16 bit

  struct {
    unsigned imm : 7;
    unsigned r2 : 3;
    unsigned r1 : 3;
    unsigned opcode : 3;
  } bits; // 16 bit

} MachineCode16bit;

int main() {
  printf("Size of MachineCode16bit = %d Bytes.\n", (int)sizeof(MachineCode16bit));

  // 0x8401 is 1000010000000001 in binary
  MachineCode16bit input = {.codeVal = 0x8401};

  // clang-format off
  printf("Opcode = %u;\nr1 = %u;\nr2 = %u;\nImm = %u;\n", 
    input.bits.opcode, input.bits.r1, input.bits.r2, input.bits.imm);
  // clang-format on

  return 0;
}
