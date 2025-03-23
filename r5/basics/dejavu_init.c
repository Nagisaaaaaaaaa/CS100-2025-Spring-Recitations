#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Basic structure
// You should be able to draft this easily within 5 minute.

int main(void) {

  unsigned num_world = 0;
  unsigned num_event = 0;
  scanf("%u%u", &num_world, &num_event);

  // Initailize worldline
  for (unsigned idw = 1; idw < num_world; idw++) {
    // Read input
    unsigned int in_sval = 0;
    scanf("%u", &in_sval);
    // ...
  }

  // Handle event
  for (unsigned ide = 1; ide < num_event; ide++) {
    // Read input
    unsigned int init_idx = 0;
    unsigned int next_idx = 0;
    scanf("%u%u", &init_idx, &next_idx);
    // ...
  }

  // Find smallest singularity value and output
  int min_val = 0;
  unsigned min_idx = 0;
  printf("%u\n", min_idx);
  printf("%d\n", min_val);

  return 0;
}
