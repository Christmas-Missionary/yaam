#define CE_INCLUDE_NORET
#include "custom_errors.h"


// clang-format off
#define ERR_STR \
  "%s File: \33[38;5;51m%s\33[0m, Func: \33[38;5;51m%s\33[0m, Line: \33[38;5;51m%d\33[0m, Message: " \
  "\33[38;5;51m%s\33[0m, Expression: \33[38;5;51m%s\33[0m\n"
// clang-format on

#ifdef __cplusplus
  #include <cstdio>
extern "C" {
#else
  #include <stdio.h>
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
