#ifndef CE_CUSTOM_ERRORS
#define CE_CUSTOM_ERRORS

#ifdef NDEBUG

// Wipes everything inside it, including calls to other funcs/macros
#define CE_ERROR(exp, type, msg)
#define CE_WARNING(exp, type, msg)

#else // #if !NDEBUG

// discount enum
#define CE_ERROR_TYPE_REGULAR 0
// From an external user

#define CE_ERROR_TYPE_FATAL 1
// Internal error

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

// `CE_NO_RET` helps static analyzers determine if code is reachable.
// If it isn't, there are less false positives.
#ifndef CE_NO_RET
#define CE_NO_RET
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

#endif // !DNDEBUG

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
