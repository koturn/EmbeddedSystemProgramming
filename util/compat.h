#ifndef COMPAT_H
#define COMPAT_H


#if defined(_MSC_VER)
#  define __PRETTY_FUNCTION__  __FUNCSIG__
#elif defined(__GNUC__)
#  define __FUNCSIG__          __PRETTY_FUNCTION__
#endif

#if !defined(__GNUC__) && defined(_MSC_VER)
#  define __attribute__(attr)  _declspec(attr)
#else
#  define __attribute__(attr)
#endif

#if !defined(_MSC_VER) && defined(__GNUC__)
#  define _declspec(attr)  __attribute__((attr))
#else
#  define _declspec(attr)
#endif

#if defined(_MSC_VER)
#  define DLLIMPORT  __declspec(dllimport)
#elif defined(__GNUC__)
#  define DLLIMPORT  __attribute__((dllimport))
#else
#  define DLLIMPORT
#endif

#if defined(_MSC_VER)
#  define DLLEXPORT  __declspec(dllexport)
#elif defined(__GNUC__)
#  define DLLEXPORT  __attribute__((dllexport))
#else
#  define DLLEXPORT
#endif




#if !defined(__GNUC__) || defined(__MINGW32__)
# define __GNUC_PREREQ(major, minor) \
  (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))
#endif

#define GNUC_PREREQ(major, minor) \
  (defined(__GNUC__) && __GNUC_PREREQ(major, minor))
#define CLANG_PREREQ(major, minor) \
  (defined(__clang__) && (__clang_major__ > (major) || (__clang_major__ == (major) && __clang_minor__ >= (minor))))
#define SUPPORT_C99 \
  (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#define SUPPORT_C11 \
  (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
#define SUPPORT_CXX11 \
  (__cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__))
#define SUPPORT_CXX14 \
  (__cplusplus >= 201300L)




/* FORCEINLINE */
#if (defined _MSC_VER) || (defined __INTEL_COMPILER)
#  define FORCEINLINE  __forceinline
#else
#  define FORCEINLINE  inline
#endif

/* ALWAYSINLINE */
#if GNUC_PREREQ(4, 0)
#  define ALWAYSINLINE  __attribute__((always_inline)) inline
#else
#  define ALWAYSINLINE  FORCEINLINE
#endif

/* NOINLINE */
#if defined(__GNUC__)
#  define NOINLINE  __attribute__((noinline))
#elif defined(_MSC_VER)
#  define NOINLINE  __declspec(noinline)
#else
#  define NOINLINE
#endif




/* ------------------------------------------------------------------------- +
 * C99 compatibility                                                         *
 * ------------------------------------------------------------------------- */
#if defined(_MSC_VER) || SUPPORT_C99
#  define __func__  __FUNCTION__
#endif


/* Macros for inline-directive under various environments */
#ifndef __cplusplus
#  if defined(_MSC_VER)
#    define inline      __inline
#    define __inline__  __inline
#  elif !defined(__GNUC__) && !SUPPORT_C99
#    define inline
#    define __inline
#  endif
#endif


/* Macros for restrict-qualifier under various environmets */
#if _MSC_VER >= 1400
#  define restrict      __restrict
#  define __restrict__  __restrict
#elif __cplusplus
#  define restrict      __restrict
#elif !SUPPORT_C99
#  if defined(__GNUC__)
#    define restrict    __restrict
#  else
#    define restrict
#    define __restrict
#    define __restrict__
#  endif
#endif




/* ------------------------------------------------------------------------- *
 * C11 compatibility                                                         *
 * ------------------------------------------------------------------------- */
// for static_assert
#if (defined(_MSC_VER) && _MSC_VER >= 1600) || \
    !SUPPORT_C11 && \
      ((SUPPORT_CXX11 && GNUC_PREREQ(4, 3)) || \
       (SUPPORT_CXX11 && CLANG_PREREQ(2, 9)))
#  define _Static_assert(expr, msg)  static_assert(expr, msg)
#else
#  define _Static_assert(expr, msg) \
     typedef char __STATIC_ASSERT_ARRAY__[(expr) ? 1 : -1]
#endif


/* _Noreturn */
#if SUPPORT_CXX11 && (GNUC_PREREQ(4, 8) || CLANG_PREREQ(3, 3))
#  define _Noreturn  [[noreturn]]
#elif defined(_MSC_VER) && _MSC_VER >= 1300
#  define _Noreturn  __declspec(noreturn)
#elif defined(__GNUC__)
#  define _Noreturn  __attribute__((noreturn))
#else
#  define _Noreturn
#endif


/* _Alignas */
#if !((SUPPORT_CXX11 && GNUC_PREREQ(4, 8)) || \
      (SUPPORT_CXX11 && CLANG_PREREQ(3, 3)))
#  if defined(_MSC_VER) && (1300 <= _MSC_VER && _MSC_VER < 1800)
#    define _Alignas(n)  __declspec(align(n))
#  elif defined(__GNUC__)
#    define _Alignas(n)  __attribute__((aligned(n)))
#  endif
#endif


/* _Thread_local */
#if !SUPPORT_CXX11 || \
  (SUPPORT_CXX11 && !GNUC_PREREQ(4, 8)) && \
  (SUPPORT_CXX11 && !CLANG_PREREQ(3, 3))
#  if defined(_MSC_VER) && _MSC_VER >= 1600
#    define _Thread_local  __declspec(thread)
#  elif defined(__GNUC__)
#    define _Thread_local  __thread
#  endif
#endif




#if !defined(__GNUC__) || defined(__MINGW32__)
#  undef __GNUC_PREREQ
#endif
#undef SUPPORT_C99
#undef SUPPORT_C11
#undef SUPPORT_CXX11
#undef SUPPORT_CXX14
#undef GNUC_PREREQ
#undef CLANG_PREREQ


#endif  /* COMPAT_H */
