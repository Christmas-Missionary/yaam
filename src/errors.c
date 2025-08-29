#ifndef NDEBUG

#define CUSTOM_ERRORS_INCLUDE_NORET
#include "../src/errors.h"

#ifdef __cplusplus
extern "C" {
#endif

ERR_NO_RET void abort(void);
int printf(const char * fmt, ...);

static inline const char * typetostr(const unsigned char type) {
  switch (type) {
    case ERROR_TYPE_WARNING:
      return "\33[38;5;226mWarning!\33[0m";
    case ERROR_TYPE_ASSERTION:
      return "\33[38;5;208mError!\33[0m";
    case ERROR_TYPE_FATAL:
    default:
      return "\33[38;5;196mFatal Error!\33[0m";
  }
}

// clang-format off
#define ERR_STR \
  "%s File: \33[38;5;51m%s\33[0m, Func: \33[38;5;51m%s\33[0m, Line: \33[38;5;51m%d\33[0m, Message: " \
  "\33[38;5;51m%s\33[0m, Expression: \33[38;5;51m%s\33[0m\n"
// clang-format on

extern void warn_handler(const char * msg, const char * file, const char * fnc, int line, const char * exp) {
  (void)printf(ERR_STR, typetostr(ERROR_TYPE_WARNING), file, fnc, line, msg, exp);
}

ERR_NO_RET
extern void err_handler(unsigned char type, const char * msg, const char * file, const char * fnc, int line,
                        const char * exp) {
  (void)printf(ERR_STR, typetostr(type), file, fnc, line, msg, exp);
  (void)printf("\33[38;5;196mAborting Now!\33[0m\n");
  abort();
}

#ifdef __cplusplus
}
#endif


#endif // NDEBUG
