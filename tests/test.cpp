#include "../src/errors.h"

int main() {
  ERROR(1 != 1, ERROR_TYPE_WARNING, "Pass");
  ERROR(true, ERROR_TYPE_ASSERTION, "Pass");
  ERROR(true, ERROR_TYPE_FATAL, "Pass");
  ERROR(false, ERROR_TYPE_WARNING, "Test One");
  ERROR(false, ERROR_TYPE_ASSERTION, "Test Two");
  return 0;
}
