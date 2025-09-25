#ifndef NDEBUG
// wipes everything if NDEBUG is defined
// No need to exclude this file in a release build, but is recommended

#define CUSTOM_ERRORS_INCLUDE_NORET
#include "custom_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

// clang-format off
#define ERR_STR \
  "%s File: \33[38;5;51m%s\33[0m, Func: \33[38;5;51m%s\33[0m, Line: \33[38;5;51m%d\33[0m, Message: " \
  "\33[38;5;51m%s\33[0m, Expression: \33[38;5;51m%s\33[0m\n"
// clang-format on

#ifdef _WIN32
// printf could be inlined, which requires definition, which I'm not touching
#include <stdio.h>
#else
int printf(const char * fmt, ...);
#endif

extern void ce_warn_handler(const char * msg, const char * file, const char * fnc, int line, const char * expr) {
  (void)printf(ERR_STR, "\33[38;5;226mWarning!\33[0m", file, fnc, line, msg, expr);
}

CE_NO_RET
extern void ce_err_handler(unsigned char type, const char * msg, const char * file, const char * fnc, int line,
                           const char * expr) {
  (void)printf(ERR_STR, (type) ? "\33[38;5;196mFatal Error!\33[0m" : "\33[38;5;208mError!\33[0m", file, fnc, line, msg,
               expr);
  (void)printf("\33[38;5;196mAborting Now!\33[0m\n");
  CE_NO_RET void abort(void);
  abort();
}

#ifdef __cplusplus
}
#endif


#endif // NDEBUG
