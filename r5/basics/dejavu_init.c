#include <assert.h>
#include <cstdint>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define WORLDLINE_NUM_LIMIT 1001
#define EVENT_NUM_LIMIT     4001

// Basic structure
// You should be able to draft this easily within 5 minute.

int main(void) {

  unsigned num_world = 0;
  unsigned num_event = 0;
  scanf("%u%u", &num_world, &num_event);

  assert((num_world < WORLDLINE_NUM_LIMIT) && (num_event < EVENT_NUM_LIMIT));

  // Initailize worldline
  for (unsigned idw = 1; idw < num_world; idw++) {
    // Read input
    unsigned in_sval = 0;
    scanf("%u", &in_sval);
    // ...
  }

  // Handle event
  for (unsigned ide = 1; ide < num_event; ide++) {
    // Read input
    unsigned init_idx = 0;
    unsigned next_idx = 0;
    scanf("%u%u", &init_idx, &next_idx);
    // ...
  }

  // Find smallest singularity value and output
  unsigned min_idx = WORLDLINE_NUM_LIMIT; // idx, loc, pos, where
  unsigned min_val = UINT32_MAX;
  printf("%u\n", min_idx);
  printf("%u\n", min_val);

  return 0;
}
