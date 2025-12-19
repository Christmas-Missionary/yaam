/*
Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License
*/

#ifndef YAM_TASTES_OKAY_I_GUESS
#define YAM_TASTES_OKAY_I_GUESS

/* `YAAM_NO_RET` helps static analyzers determine if code is reachable. */
/* If it isn't, there are less false positives. */
#ifdef __cplusplus
  #if (defined(_MSC_VER) && _MSVC_LANG >= 201103L) || (__cplusplus >= 201103L)
    #define YAAM_NO_RET [[noreturn]]
  #endif
#elif defined(__STDC_VERSION__)
  #if __STDC_VERSION__ >= 202311L
    #define YAAM_NO_RET [[noreturn]]
  #elif __STDC_VERSION__ >= 201112L
    #define YAAM_NO_RET _Noreturn
  #endif
#endif
#ifndef YAAM_NO_RET
  #define YAAM_NO_RET
#endif

#if defined(YAAM_NONE)
  #define YAAM_WARN(expr, msg) ((void)0)
  #define YAAM_ERROR(expr, msg) ((void)0)
  #define YAAM_FATAL(expr, msg) ((void)0)
#else /* if no YAAM_NONE */

  #if defined(YAAM_NO_WARN)
    #define YAAM_WARN(expr, msg) ((void)0)
  #elif defined(YAAM_ASSUME_WARN) || defined(YAAM_ASSUME_ALL)

    #if (defined(_MSVC_LANG) && _MSVC_LANG >= 202302L) || (defined(__cplusplus) && __cplusplus >= 202302L)
      #define YAAM_WARN(expr, msg) [[assume(expr)]]
    #elif defined(_MSC_VER) /* #if Not C++23 */
      #define YAAM_WARN(expr, msg) __assume(expr)
    #elif defined(__clang__) || defined(__EMSCRIPTEN__) /* Not MSVC, but Clang or Emscripten */
      #define YAAM_WARN(expr, msg) __builtin_assume(expr)
    #elif defined(__GNUC__) /* Not Clang, but GCC */
      #define YAAM_WARN(expr, msg) __attribute__((assume(expr)))
    #else /* None of the above */
      #define YAAM_WARN(expr, msg) ((void)0)
    #endif /* #ifdef YAAM_ASSUME */

  #endif /* YAAM_ASSUME_WARN or YAAM_ASSUME_ALL */

  #if defined(YAAM_NO_ERROR)
    #define YAAM_ERROR(expr, msg) ((void)0)
  #elif defined(YAAM_ASSUME_ERROR) || defined(YAAM_ASSUME_ALL)

    #if (defined(_MSVC_LANG) && _MSVC_LANG >= 202302L) || (defined(__cplusplus) && __cplusplus >= 202302L)
      #define YAAM_ERROR(expr, msg) [[assume(expr)]]
    #elif defined(_MSC_VER) /* #if Not C++23 */
      #define YAAM_ERROR(expr, msg) __assume(expr)
    #elif defined(__clang__) || defined(__EMSCRIPTEN__) /* Not MSVC, but Clang or Emscripten */
      #define YAAM_ERROR(expr, msg) __builtin_assume(expr)
    #elif defined(__GNUC__) /* Not Clang, but GCC */
      #define YAAM_ERROR(expr, msg) __attribute__((assume(expr)))
    #else /* None of the above */
      #define YAAM_ERROR(expr, msg) ((void)0)
    #endif /* #ifdef YAAM_ASSUME */

  #endif /* YAAM_ASSUME_ERROR or YAAM_ASSUME_ALL */

  #if defined(YAAM_NO_FATAL)
    #define YAAM_FATAL(expr, msg) ((void)0)
  #elif defined(YAAM_ASSUME_FATAL) || defined(YAAM_ASSUME_ALL)

    #if (defined(_MSVC_LANG) && _MSVC_LANG >= 202302L) || (defined(__cplusplus) && __cplusplus >= 202302L)
      #define YAAM_FATAL(expr, msg) [[assume(expr)]]
    #elif defined(_MSC_VER) /* #if Not C++23 */
      #define YAAM_FATAL(expr, msg) __assume(expr)
    #elif defined(__clang__) || defined(__EMSCRIPTEN__) /* Not MSVC, but Clang or Emscripten */
      #define YAAM_FATAL(expr, msg) __builtin_assume(expr)
    #elif defined(__GNUC__) /* Not Clang, but GCC */
      #define YAAM_FATAL(expr, msg) __attribute__((assume(expr)))
    #else /* None of the above */
      #define YAAM_FATAL(expr, msg) ((void)0)
    #endif /* #ifdef YAAM_ASSUME */

  #endif /* YAAM_ASSUME_FATAL or YAAM_ASSUME_ALL */

#endif /* if no YAAM_NONE */

#if defined(__STDC_VERSION__)
  #if __STDC_VERSION__ == 199409L
    #define __func__ ""
  #endif
#elif (defined(__cplusplus) && __cplusplus >= 201103L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
  /* Nothing */
#else /* If not C++ and no C version */
  #define __func__ ""
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(YAAM_ERROR) || !defined(YAAM_FATAL)
YAAM_NO_RET
void yaam_err_handler(unsigned char type, const char * msg, const char * file, const char * fnc, int line,
                      const char * expr);
  #if !defined(YAAM_ERROR)
    #define YAAM_ERROR(expr, msg) ((expr) ? (void)0 : yaam_err_handler(0, msg, __FILE__, __func__, __LINE__, #expr))
  #endif
  #if !defined(YAAM_FATAL)
    #define YAAM_FATAL(expr, msg) ((expr) ? (void)0 : yaam_err_handler(1, msg, __FILE__, __func__, __LINE__, #expr))
  #endif
#endif

#if !defined(YAAM_WARN)
void yaam_warn_handler(const char * msg, const char * file, const char * fnc, int line, const char * expr);
  #define YAAM_WARN(expr, msg) ((expr) ? (void)0 : yaam_warn_handler(msg, __FILE__, __func__, __LINE__, #expr))
#endif

#define NOT_ON_WINDOWS 268435456UL /* Has 29th bit on, reserved for apps, system always has this bit off */
#ifdef _WIN32
unsigned long set_windows_colors(void);
#else
  #define set_windows_colors() (NOT_ON_WINDOWS)
#endif

#ifdef __cplusplus
}
#endif

/* convenience macro for noreturn, if needed */
#ifndef YAAM_INCLUDE_NORET
  #undef YAAM_NO_RET
#endif

/* convenience macro for static_assert, if in C */
#ifndef __cplusplus
  #if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
    #define static_assert(expr, msg)
    #define _Static_assert(expr, msg)
  #elif (__STDC_VERSION__ >= 202311L)
    #define _Static_assert static_assert
  #else /* At least C11, before C23 */
    #define static_assert _Static_assert
  #endif
#elif (defined(_MSC_VER) && _MSVC_LANG < 201103L) || (__cplusplus < 201103L && !defined(_MSC_VER))
  #define static_assert(expr, msg)
  #define _Static_assert(expr, msg)
#endif /* ifndef __cplusplus */


#endif /* YAM_TASTES_OKAY_I_GUESS */
