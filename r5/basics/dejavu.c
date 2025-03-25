/*

  This piece of source code corresponds to:
  Homework2, Problem5 - `Deja Vu!`

  ! Baseline:
  ! 1. You should fully understand this implementation.
  ! 2. You should be familiar with the bit operations, struct definition we used.
  ! 3. You should be familiar with pointer access for structs.
  * Bonus:
  * 4. Apply this style to your own homework implementation and have fun!

*/

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WORLDLINE_NUM_LIMIT 1001
#define EVENT_NUM_LIMIT     4001

typedef uint32_t u32;

u32 cycleLShift(u32 x, u32 bit_to_shift) {

  bit_to_shift %= 32;

  // Make it robust!
  if (bit_to_shift == 0) {
    return x;
  }

  // Now, 1 <= bit_to_shift <= 31:
  u32 high_to_low = x >> (32 - bit_to_shift);
  u32 low_to_high = x << bit_to_shift;
  return high_to_low | low_to_high;
}

struct WorldLine_ {
  u32 sval;                   // singularity value
  struct WorldLine_ *outedge; // points to another worldline
  bool modified;
}; // Or "Sekaisen", whatever...

typedef struct WorldLine_ WorldLine;

int main(void) {

  assert(sizeof(unsigned) == sizeof(u32)); // Compatible?

  u32 num_world = 0; // num, size, dim, scale, cap, vol, ...
  u32 num_event = 0;
  scanf("%u%u", &num_world, &num_event);

  // Input examination
  assert((num_world < WORLDLINE_NUM_LIMIT) && (num_event < EVENT_NUM_LIMIT));

  WorldLine *wdlines = calloc(num_world + 1, sizeof(WorldLine));

  // Initailize worldline
  for (u32 idw = 1; idw <= num_world; idw++) {
    u32 in_sval = 0;
    scanf("%u", &in_sval);

    WorldLine *curr = wdlines + idw; // equals to &wdlines[idw]
    curr->sval = in_sval;
    curr->outedge = curr;
    curr->modified = false;
  }

  // handle event
  for (u32 ide = 1; ide <= num_event; ide++) {
    // clear modification record
    for (u32 idw = 1; idw <= num_world; idw++) {
      wdlines[idw].modified = false;
    }

    // read input
    u32 init_idx = 0;
    u32 next_idx = 0;
    scanf("%u%u", &init_idx, &next_idx);

    WorldLine *prev = wdlines + init_idx;
    WorldLine *next = wdlines + next_idx;

    prev->outedge = next;
    prev->modified = true;

    u32 transit_stp = 1;
    u32 base_sval = prev->sval;

    // core logic
    while ((!next->modified)) {

      // Sekaisen changing
      (next->sval) ^= cycleLShift(base_sval, transit_stp);

      // update: march one step
      next->modified = true;
      prev = next;
      next = next->outedge;

      ++transit_stp;
    }
  }

  // find smallest singularity value and output

  u32 min_val = UINT32_MAX;
  u32 min_idx = WORLDLINE_NUM_LIMIT; // idx, loc, pos, where

  for (u32 idw = 1; idw <= num_world; ++idw) {
    if (wdlines[idw].sval < min_val) {
      min_val = wdlines[idw].sval;
      min_idx = idw;
    }
  }
  assert(min_idx < WORLDLINE_NUM_LIMIT);

  printf("%u\n", min_idx);
  printf("%u\n", min_val);

  free(wdlines);
  return 0;
}
