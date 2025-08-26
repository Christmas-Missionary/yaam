#ifndef NDEBUG

#include "../src/errors.h"

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char * fmt, ...);
void abort(void);

static inline const char * typetostr(const ERROR_TYPE type) {
  switch (type) {
    case ERROR_TYPE_WARNING:
      return "\33[38;5;226mWarning!\33[0m";
    case ERROR_TYPE_ASSERTION:
      return "\33[38;5;208mError!\33[0m";
    case ERROR_TYPE_FATAL:
      return "\33[38;5;196mFatal Error!\33[0m";
  }
  return "";
}

extern void ERROR(bool exp, ERROR_TYPE type, const char * msg, const error_source src) {
  if (!exp) {
    (void)printf("%s File: \33[38;5;51m%s\33[0m -> Function: \33[38;5;51m%s\33[0m -> Line: \33[38;5;51m%lu\33[0m, "
                 "Message: \33[38;5;51m%s\33[0m\n",
                 typetostr(type), src.file, src.func, src.line, msg);
    if (type != ERROR_TYPE_WARNING) {
      (void)printf("\33[38;5;196mAborting Now!\33[0m\n");
      abort();
    }
  }
}

#ifdef __cplusplus
}
#endif


#endif // NDEBUG
