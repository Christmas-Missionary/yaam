#include "../src/errors.h"
#include <stdbool.h>

#ifdef CODE_CHECK
#error "Currently doing static analysis. This error was emitted to prevent object files from being written."
#endif

int main(void) {
  ERROR(1 != 1, ERROR_TYPE_WARNING, "Pass", ERROR_SRC);
  ERROR(1, ERROR_TYPE_ASSERTION, "Pass", ERROR_SRC);
  ERROR(1, ERROR_TYPE_FATAL, "Pass", ERROR_SRC);
  ERROR(0, ERROR_TYPE_WARNING, "Test One", ERROR_SRC);
  ERROR(0, ERROR_TYPE_ASSERTION, "Test Two", ERROR_SRC);
  return 0;
}
