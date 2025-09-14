#include "../src/custom_errors.h"
#include <chrono>
#include <iostream>
#include <random>

char stuff(int num) {
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
      CE_ERROR(false, "Number is between 1 and 10 inclusive!", CE_ERROR_TYPE_REGULAR);
      return 0;
  }
}

int main() {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(1, 10);

  using namespace std::chrono;
  auto start = high_resolution_clock::now();
  int to_print = 0;
  for (int i = 0; i < 100'000'000; i++) {
    to_print = dist(rng);
  }
  long long duration_count = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
  std::cout << "Time was " << duration_count << " milliseconds.\nNumber is " << to_print << '\n';
  return 0;
}
