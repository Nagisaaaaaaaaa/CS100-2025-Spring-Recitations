#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WORLDLINE_NUM_LIMIT 1001
#define EVENT_NUM_LIMIT     4001

typedef uint32_t u32;

u32 cycleShift(u32 x, size_t bit_to_shift) {

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
  u32 sval; // singularity
  struct WorldLine_ *outedge;
  bool modified;
}; // Or "Sekaisen", whatever...

typedef struct WorldLine_ WorldLine;

int main(void) {

  assert(sizeof(unsigned) == sizeof(u32)); // Compatible?

  unsigned num_world = 0; // num, size, dim, scale, cap, vol, ...
  unsigned num_event = 0;
  scanf("%u%u", &num_world, &num_event);

  // Input examination
  assert((num_world < WORLDLINE_NUM_LIMIT) && (num_event < EVENT_NUM_LIMIT));

  WorldLine *wdlines = calloc(num_world + 1, sizeof(WorldLine));

  // Initailize worldline
  for (unsigned idw = 1; idw <= num_world; idw++) {
    unsigned int in_sval = 0;
    scanf("%u", &in_sval);

    WorldLine *curr = wdlines + idw; // &wdlines[idw]
    curr->sval = (u32)in_sval;
    curr->outedge = curr;
    curr->modified = false;
  }

  // handle event
  for (unsigned ide = 1; ide <= num_event; ide++) {
    // clear modification record
    for (unsigned idw = 1; idw <= num_world; idw++) {
      wdlines[idw].modified = false;
    }

    // read input
    unsigned int init_idx = 0;
    unsigned int next_idx = 0;
    scanf("%u%u", &init_idx, &next_idx);

    WorldLine *prev = wdlines + init_idx;
    WorldLine *next = wdlines + next_idx;

    prev->outedge = next;
    prev->modified = true;

    size_t transit_stp = 1;
    u32 base_sval = prev->sval;

    // Core logic
    while ((!next->modified)) {

      // Sekaisen changing
      (next->sval) ^= cycleShift(base_sval, transit_stp);

      // Update
      next->modified = true;
      prev = next;
      next = next->outedge;

      ++transit_stp;
    }
  }

  // Find smallest singularity value and output
  u32 min_val = UINT32_MAX;
  unsigned min_idx = WORLDLINE_NUM_LIMIT; // idx, loc, pos, where
  for (unsigned int idw = 1; idw <= num_world; ++idw) {
    if (wdlines[idw].sval < min_val) {
      min_val = wdlines[idw].sval;
      min_idx = idw;
    }
  }
  printf("%d\n", (int)min_idx);
  printf("%d\n", (int)min_val);

  free(wdlines);
  return 0;
}
