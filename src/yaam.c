/*
Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License
*/

#define YAAM_INCLUDE_NORET
#include "yaam.h"


/* clang-format off */
#ifdef __func__
  #define ERR_STR \
    "%s File: \33[38;5;51m%s\33[0m, \33[38;5;226mFunc not available\33[0m%s, Line: \33[38;5;51m%d\33[0m, Message: " \
    "\33[38;5;51m%s\33[0m, Expression: \33[38;5;51m%s\33[0m\n"
#else
  #define ERR_STR \
    "%s File: \33[38;5;51m%s\33[0m, Func: \33[38;5;51m%s\33[0m, Line: \33[38;5;51m%d\33[0m, Message: " \
    "\33[38;5;51m%s\33[0m, Expression: \33[38;5;51m%s\33[0m\n"
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
  (void)printf(ERR_STR, "\33[38;5;226mWarning!\33[0m", file, fnc, line, msg, expr);
}

YAAM_NO_RET
void yaam_err_handler(int type, const char * msg, const char * file, const char * fnc, int line, const char * expr) {
  (void)printf(ERR_STR, (type) ? "\33[38;5;196mFatal Error!\33[0m" : "\33[38;5;208mError!\33[0m", file, fnc, line, msg,
               expr);
  (void)printf("\33[38;5;196mAborting Now!\33[0m\n");
  abort();
}

#ifdef _WIN32

  #include <windows.h>
unsigned long set_windows_colors(void) {
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
