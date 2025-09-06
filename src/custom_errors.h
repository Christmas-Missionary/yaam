#ifndef CE_CUSTOM_ERRORS
#define CE_CUSTOM_ERRORS

#ifdef NDEBUG

#define CE_ERROR(exp, type, msg)

#else // #if !NDEBUG

#if defined(__cplusplus) && __cplusplus < 201103L
#error "C++ version is too early! It must be at least C++11!"
#elif !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ == 199409L)
#error "You must be using C89, which is not allowed! Please be at least C99!"
#endif

#define CE_ERROR_TYPE_WARNING 0
#define CE_ERROR_TYPE_ASSERTION 1
#define CE_ERROR_TYPE_FATAL 2

#ifdef __cplusplus
#define CE_NO_RET [[noreturn]]
extern "C" {
#endif

#if defined(__STDC_VERSION__) && !defined(CE_NO_RET)
#if __STDC_VERSION__ >= 202311L
#define CE_NO_RET [[noreturn]]
#elif __STDC_VERSION__ >= 201112L
#define CE_NO_RET _Noreturn
#endif
#endif

#ifndef CE_NO_RET
#define CE_NO_RET
#endif

CE_NO_RET
void ce_err_handler(unsigned char type, const char * msg, const char * file, const char * fnc, int line, const char * exp);

void ce_warn_handler(const char * msg, const char * file, const char * fnc, int line, const char * exp);

#ifdef __cplusplus
}
#endif

// clang-format off
#define CE_ERROR(exp, type, msg) \
  ((exp)    ? (void)0 \
   : (type) ? ce_err_handler(type, msg, __FILE_NAME__, __func__, __LINE__, #exp) \
            : ce_warn_handler(msg, __FILE_NAME__, __func__, __LINE__, #exp))
// clang-format on

#ifndef CUSTOM_ERRORS_INCLUDE_NORET
#undef CE_NO_RET
#endif

#endif // !DNDEBUG

#if !defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && __STDC_VERSION__ < 202311L
#define static_assert _Static_assert
#endif

#endif // CE_CUSTOM_ERRORS
