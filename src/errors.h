#ifndef CUSTOM_ERRORS
#define CUSTOM_ERRORS

#ifdef NDEBUG

#define ERROR(exp, type, msg)

#else /* #if !NDEBUG */

#define ERROR_TYPE_WARNING 0
#define ERROR_TYPE_ASSERTION 1
#define ERROR_TYPE_FATAL 2

#ifdef __cplusplus
#define ERR_NO_RET [[noreturn]]
extern "C" {
#endif

#if defined(__STDC_VERSION__) && !defined(ERR_NO_RET)
#if __STDC_VERSION__ >= 202311L
#define ERR_NO_RET [[noreturn]]
#elif __STDC_VERSION__ >= 201112L
#define ERR_NO_RET _Noreturn
#endif
#endif

#ifndef ERR_NO_RET
#define ERR_NO_RET
#endif

ERR_NO_RET
void err_handler(unsigned char type, const char * msg, const char * file, const char * fnc, int line, const char * exp);

void warn_handler(const char * msg, const char * file, const char * fnc, int line, const char * exp);

#ifdef __cplusplus
}
#endif

/* clang-format off */
#define ERROR(exp, type, msg) \
  ((exp)    ? (void)0 \
   : (type) ? err_handler(type, msg, __FILE_NAME__, __func__, __LINE__, #exp) \
            : warn_handler(msg, __FILE_NAME__, __func__, __LINE__, #exp))
/* clang-format on */

#ifndef CUSTOM_ERRORS_INCLUDE_NORET
#undef ERR_NO_RET
#endif

#endif /* !DNDEBUG */

#endif /* CUSTOM_ERRORS */
