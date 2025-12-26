/*
Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License
*/

#define YAAM_INCLUDE_NORET
#include "yaam.h"

#ifdef YAAM_NO_COLORS
  #define YAAM_COLOR(str)
  #define YAAM_CLEAR
  #define YAAM_BOLD(str)
#else
  #define YAAM_COLOR(str) "\33[" str "m"
  #define YAAM_CLEAR "\33[0m"
  #define YAAM_BOLD(str) "\33[1m\33[" str "m"
#endif

/* clang-format off */

#ifdef __func__
  #define ERR_STR \
    "%s File: " YAAM_COLOR("38;5;46") "%s" YAAM_CLEAR ", " YAAM_BOLD("38;5;201") "Func not available" YAAM_CLEAR "%s, " \
    "Line: " YAAM_COLOR("38;5;46") "%d" YAAM_CLEAR ", Message: " YAAM_COLOR("38;5;51") "%s" YAAM_CLEAR ", Expression: " \
    YAAM_COLOR("38;5;51") "%s" YAAM_CLEAR "\n"
#else
  #define ERR_STR \
    "%s File: " YAAM_COLOR("38;5;46") "%s" YAAM_CLEAR ", Func: " YAAM_COLOR("38;5;46") "%s" YAAM_CLEAR ", " \
    "Line: " YAAM_COLOR("38;5;46") "%d" YAAM_CLEAR ", Message: " YAAM_COLOR("38;5;51") "%s" YAAM_CLEAR ", Expression: " \
    YAAM_COLOR("38;5;51") "%s" YAAM_CLEAR "\n"
#endif

/* clang-format on */

#ifdef __cplusplus
  #include <cstdio>
  #include <cstdlib>
extern "C" {
#else
  #include <stdio.h>
  #include <stdlib.h>
#endif

void yaam_warn_handler(const char * msg, const char * file, const char * fnc, int line, const char * expr) {
  (void)printf(ERR_STR, YAAM_COLOR("38;5;226") "Warning!" YAAM_CLEAR, file, fnc, line, msg, expr);
}

YAAM_NO_RET
void yaam_err_handler(int type, const char * msg, const char * file, const char * fnc, int line, const char * expr) {
  (void)printf(ERR_STR,
               (type) ? (YAAM_BOLD("38;5;196") "Fatal Error!" YAAM_CLEAR) : (YAAM_BOLD("38;5;208") "Error!" YAAM_CLEAR),
               file, fnc, line, msg, expr);
  (void)printf(YAAM_COLOR("38;5;196") "Aborting Now!" YAAM_CLEAR "\n");
  abort();
}

#ifdef _WIN32

  #include <windows.h>
unsigned long yaam_set_windows_colors(void) {
  DWORD mode = 0;
  HANDLE con = GetStdHandle(STD_OUTPUT_HANDLE);
  if (con == INVALID_HANDLE_VALUE || !GetConsoleMode(con, &mode)) {
    return (unsigned long)(GetLastError());
  }
  mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  if (!SetConsoleMode(con, mode)) {
    return (unsigned long)(GetLastError());
  }
  return 0UL;
}

#endif

#ifdef __cplusplus
}
#endif
