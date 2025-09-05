#include "../src/errors.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>

static inline double clockdif_to_milli(const clock_t time) {
  return ((double)time / CLOCKS_PER_SEC) * 1000;
}

static inline const char * typetostr(const int type) {
  switch (type) {
    case CE_ERROR_TYPE_WARNING:
      return "warning:";
    case CE_ERROR_TYPE_ASSERTION:
      return "assert: ";
    case CE_ERROR_TYPE_FATAL:
      return "fatal:  ";
    default:
      CE_ERROR(0, CE_ERROR_TYPE_FATAL, "Number is not part of discount enum!");
      return "";
  };
}

#define VAL_TO_TEST 5
#define LOOP_AMOUNT 1500000000


int main(void) {
  const int test = VAL_TO_TEST;
  for (int j = 0; j < 3; j++) {
    clock_t time = clock();
    for (int i = 0; i < LOOP_AMOUNT; i++) {
      assert(test == VAL_TO_TEST);
    }
    time = clock() - time;
    printf("Libc assert:    %f milliseconds\n", clockdif_to_milli(time));

    time = clock();
    for (int i = 0; i < LOOP_AMOUNT; i++) {
      CE_ERROR(test == VAL_TO_TEST, i, "");
    }
    time = clock() - time;
    printf("Errors %s %f milliseconds\n", typetostr(j), clockdif_to_milli(time));
  }
  return 0;
}
