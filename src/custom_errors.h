#ifndef CE_CUSTOM_ERRORS
#define CE_CUSTOM_ERRORS

#ifdef __cplusplus
#define CE_NO_RET [[noreturn]]
#endif

#if defined(__STDC_VERSION__) && !defined(CE_NO_RET)
#if __STDC_VERSION__ >= 202311L
#define CE_NO_RET [[noreturn]]
#elif __STDC_VERSION__ >= 201112L
#define CE_NO_RET _Noreturn
#endif
#endif // defined(__STDC_VERSION__) && !defined(CE_NO_RET)

// `CE_NO_RET` helps static analyzers determine if code is reachable.
// If it isn't, there are less false positives.
#ifndef CE_NO_RET
#define CE_NO_RET
#endif

#ifdef CE_ASSUME

// Wipe all warnings
#define CE_WARNING(exp, type)

#if (defined(_MSVC_LANG) && _MSVC_LANG >= 202302L) || (defined(__cplusplus) && __cplusplus >= 202302L)

#define CE_ERROR(exp, msg, type) [[assume(exp)]]

#elif defined(_MSC_VER) // #if Not C++23

#define CE_ERROR(exp, msg, type) __assume(exp)

#elif defined(__clang__) // Not MSVC, but Clang

#define CE_ERROR(exp, msg, type) __builtin_assume(exp)

#elif defined(__GNUC__) // Not Clang, but GCC

#define CE_ERROR(exp, msg, type) __attribute__((assume(exp)))

#else // None of the above

#define CE_ERROR(exp, msg, type)

#endif // #ifdef CE_ASSUME

#elif defined(NDEBUG) // #ifndef CE_ASSUME && #ifdef NDEBUG

// Wipes everything inside it, including calls to other funcs/macros
#define CE_ERROR(exp, msg, type)
#define CE_WARNING(exp, msg)

#else // #ifndef NDEBUG

// discount enum
#define CE_ERROR_TYPE_REGULAR 0
// From an external user

#define CE_ERROR_TYPE_FATAL 1
// Internal error

#ifdef __cplusplus
extern "C" {
#endif

CE_NO_RET
void ce_err_handler(unsigned char type, const char * msg, const char * file, const char * fnc, int line,
                    const char * exp);

void ce_warn_handler(const char * msg, const char * file, const char * fnc, int line, const char * exp);

#ifdef __cplusplus
}
#endif

#define CE_ERROR(exp, msg, type) ((exp) ? (void)0 : ce_err_handler(type, msg, __FILE__, __func__, __LINE__, #exp))

#define CE_WARNING(exp, msg) ((exp) ? (void)0 : ce_warn_handler(msg, __FILE__, __func__, __LINE__, #exp))

// convenience macro for noreturn, if needed
#ifndef CUSTOM_ERRORS_INCLUDE_NORET
#undef CE_NO_RET
#endif

#endif // !CE_ASSUME

// convenience macro for static_assert, if in C
#ifndef __cplusplus
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define static_assert _Static_assert
#else
#define static_assert(exp, msg)
#define _Static_assert(exp, msg)
#endif
#endif // ifndef __cplusplus

#endif // CE_CUSTOM_ERRORS
