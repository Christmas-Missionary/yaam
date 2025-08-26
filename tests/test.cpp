#include "../src/errors.h"

int main() {
  // ERROR(1 != 1, ERROR_TYPE_WARNING, "Pass", ERROR_SRC);
  // ERROR(true, ERROR_TYPE_ASSERTION, "Pass", ERROR_SRC);
  // ERROR(true, ERROR_TYPE_FATAL, "Pass", ERROR_SRC);
  // ERROR(false, ERROR_TYPE_WARNING, "Test One", ERROR_SRC);
  ERROR(false, ERROR_TYPE_ASSERTION, "Test Two", ERROR_SRC);
  return 0;
}
