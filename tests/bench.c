#include "../src/errors.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>

static inline double clockdif_to_milli(const clock_t time) {
  return ((double)time / CLOCKS_PER_SEC) * 1000;
}

#define VAL_TO_TEST 5
#define LOOP_AMOUNT 1000000000


int main(void) {
  const int test = VAL_TO_TEST;
  clock_t time = clock();
  for (int i = 0; i < LOOP_AMOUNT; i++) {
    assert(test == VAL_TO_TEST);
  }
  time = clock() - time;
  printf("Libc assert: %f milliseconds\n", clockdif_to_milli(time));

  time = clock();
  for (int i = 0; i < LOOP_AMOUNT; i++) {
    ERROR(test == VAL_TO_TEST, ERROR_TYPE_ASSERTION, "", ERROR_SRC);
  }
  time = clock() - time;
  printf("Errors assert: %f milliseconds\n", clockdif_to_milli(time));
  return 0;
}
