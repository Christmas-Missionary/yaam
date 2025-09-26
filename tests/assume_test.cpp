#include "../src/custom_errors.h"

#include <vector>

int warn(int num) {
  CE_WARN(num == 4, "Number is supposed to be 4!");
  int stuff = (num + 4) * (num - 10) * (num - 5) / 2;
  int more_stuff = stuff * 4 + (num / 3) + 20;
  return more_stuff + stuff - num;
}

char reg(int num) {
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

long fatal(std::vector<long> const & vec) {
  const auto size = vec.size();
  CE_FATAL(size == 3, "Ptr is null!");
  long res = 0;
  for (unsigned long i = 0; i < size; i++) {
    res += vec.at(i);
  }

  return res;
}
