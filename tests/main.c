#include "../src/custom_errors.h"

int warn(int num) {
  int stuff = 0;
  int more_stuff = 0;
  CE_WARN(num == 4, "Number is supposed to be 4!");
  stuff = (num + 4) * (num - 10) * (num - 5) / 2;
  more_stuff = stuff * 4 + (num / 3) + 20;
  return more_stuff + stuff - num;
}

long reg(int num) {
  CE_ERROR(num == 1, "Number is supposed to be 1!");
  switch (num) {
    case 1:
      return 10;
    case 2:
      return 38;
    case 3:
      return 28;
    case 4:
      return 40;
    case 5:
      return 12;
    case 6:
      return 56;
    case 7:
      return 30;
    case 8:
      return 99;
    case 9:
      return 3;
    case 10:
      return 76;
    default:
      return 0;
  }
}

#define VALS_SIZE 3

long fatal(const long * vals, unsigned long size) {
  long res = 0;
  unsigned long index = 0;
  CE_FATAL(size == VALS_SIZE, "Size is not 3!");
  for (; index < size; index++) {
    res += vals[index];
  }
  return res;
}

#ifdef __cplusplus
  #include <cstdio>
#else
  #include <stdio.h>
#endif

#ifdef REG_ERROR_TEST
  #define WARN_VALUE 3
  #define REG_VALUE 0
#else
  #define WARN_VALUE 4
  #define REG_VALUE 1
#endif

#ifdef FATAL_ERROR_TEST
  #define FATAL_VALUE 2
#else
  #define FATAL_VALUE VALS_SIZE
#endif

int main(void) {
  long vals[VALS_SIZE] = {0, 0, 27};
  unsigned long err = set_windows_colors();
  vals[0] = warn(WARN_VALUE);
  vals[1] = reg(REG_VALUE);
  if (err != 0 && err != NOT_ON_WINDOWS) {
    printf("Colored text output will not work on windows!\n");
  }
  fatal(vals, FATAL_VALUE);
  printf("%ld, %ld, %ld\n", vals[0], vals[1], vals[2]);
  return 0;
}
