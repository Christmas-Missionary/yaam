#ifndef CUSTOM_ERRORS
#define CUSTOM_ERRORS

#if !defined(__cplusplus) && __STDC_VERSION__ <= 201710L
#include <stdbool.h>
#endif

#ifdef NDEBUG

#define ERROR(exp, type, msg, source)

#else // #if !NDEBUG

typedef struct error_source {
  const char * file;
  const char * func;
  unsigned long line;
} error_source;

typedef enum ERROR_TYPE { ERROR_TYPE_WARNING, ERROR_TYPE_ASSERTION, ERROR_TYPE_FATAL } ERROR_TYPE;

#ifdef __cplusplus
#define ERROR_SRC ((error_source){__FILE_NAME__, __func__, static_cast<unsigned long>(__LINE__)})
#else
#define ERROR_SRC ((error_source){__FILE_NAME__, __func__, (unsigned long)__LINE__})
#endif

#ifdef __cplusplus
extern "C"
#endif
  void
  ERROR(bool exp, ERROR_TYPE type, const char * msg, error_source src);

#endif // !DNDEBUG

#endif // CUSTOM_ERRORS
