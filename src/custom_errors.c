#ifndef NDEBUG

#define CUSTOM_ERRORS_INCLUDE_NORET
#include "custom_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline const char * typetostr(const unsigned char type) {
  switch (type) {
    case CE_ERROR_TYPE_WARNING:
      return "\33[38;5;226mWarning!\33[0m";
    case CE_ERROR_TYPE_ASSERTION:
      return "\33[38;5;208mError!\33[0m";
    case CE_ERROR_TYPE_FATAL:
    default:
      return "\33[38;5;196mFatal Error!\33[0m";
  }
}

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

extern void ce_warn_handler(const char * msg, const char * file, const char * fnc, int line, const char * exp) {
  (void)printf(ERR_STR, typetostr(CE_ERROR_TYPE_WARNING), file, fnc, line, msg, exp);
}

CE_NO_RET
extern void ce_err_handler(unsigned char type, const char * msg, const char * file, const char * fnc, int line,
                           const char * exp) {
  (void)printf(ERR_STR, typetostr(type), file, fnc, line, msg, exp);
  (void)printf("\33[38;5;196mAborting Now!\33[0m\n");
  CE_NO_RET void abort(void);
  abort();
}

#ifdef __cplusplus
}
#endif


#endif // NDEBUG
