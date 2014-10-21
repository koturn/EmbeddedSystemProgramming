#ifndef UTIL_H
#define UTIL_H


#ifndef TRUE
#  define TRUE  1
#endif
#ifndef FALSE
#  define FALSE 0
#endif

#ifdef __GNUC__
#  define __DO__          (
#  define __WHILE_ZERO__  )
#else
#  define __DO__          do
#  define __WHILE_ZERO__  while (0)
#endif


/* Get the number of elements of static array */
#define LENGTH(array)  (sizeof(array) / sizeof((array)[0]))
#define length(array)  LENGTH(array)
/* Get the address of the termination of static array */
#define array_end(array)   ((array) + length(array))
/* Get the address of the last element of static array */
#define array_last(array)  ((array) + (length(array) - (size_t) 1))




/* ========================================================================= *
 * Macro about structure                                                     *
 * ========================================================================= */
#ifndef offsetof
/* Get the offset of the member in structure */
#  define offsetof(type, member)  ((size_t) &((type *) 0)->member)
#endif

/* Get the size of the member in structure */
#define memsize(type, member)  sizeof(((type *) 0)->member)
/* Get the number of the elements of the static array in structure */
#define memlength(type, mem_array)  length(((type *) 0)->mem_array)
/* Get the base address of structure by using the offset of its member */
#define struct_base_offset(type, offset, mem_addr) \
  ((type *) ((char *) (mem_addr) - (offset)))
/* Get the base address of structure by using the address of its member */
#define struct_base(type, member, mem_addr) \
  struct_base_offset((type), offsetof(type, member), (mem_addr))


/* Get bit size of variable */
#define BITSIZE(var)   (sizeof(var) << 3)
#define bitsize(var)   BITSIZE(var)




/* ========================================================================= *
 * Macros about bit-calculation                                              *
 * ========================================================================= */
/* Get specified bit status */
#define BITCHECK(a, b)  (((a) >> (b)) & 1)
#define bitcheck(a, b)  BITCHECK(a, b)

/* Set '1' to specified bit */
#define BITSET(a, b)    ((a) |= (1 << (b)))
#define bitset(a, b)    BITSET(a, b)

/* Set '0' to specified bit */
#define BITUNSET(a, b)  ((a) &= ~(1 << (b)))
#define bitunset(a, b)  BITUNSET(a, b)


/* Binary literal macro */
#define BIN_LITERAL_8(bin) \
  ( \
    ((0x0000000f & (0x ## bin))       != 0 ? 1        : 0) | \
    ((0x0000000f & (0x ## bin >> 4))  != 0 ? (1 << 1) : 0) | \
    ((0x0000000f & (0x ## bin >> 8))  != 0 ? (1 << 2) : 0) | \
    ((0x0000000f & (0x ## bin >> 12)) != 0 ? (1 << 3) : 0) | \
    ((0x0000000f & (0x ## bin >> 16)) != 0 ? (1 << 4) : 0) | \
    ((0x0000000f & (0x ## bin >> 20)) != 0 ? (1 << 5) : 0) | \
    ((0x0000000f & (0x ## bin >> 24)) != 0 ? (1 << 6) : 0) | \
    ((0x0000000f & (0x ## bin >> 28)) != 0 ? (1 << 7) : 0) \
  )

#define BIN_LITERAL_16(bin1, bin2) \
  ((BIN_LITERAL_8(bin1) << 8) | BIN_LITERAL_8(bin2))

#define BIN_LITERAL_24(bin1, bin2) \
  ( \
    (BIN_LITERAL_8(bin1) << 16) | \
    (BIN_LITERAL_8(bin2) << 8) | \
    BIN_LITERAL_8(bin3) \
  )

#define BIN_LITERAL_32(bin1, bin2, bin3, bin4) \
  ((BIN_LITERAL_16(bin1, bin2) << 16) | BIN_LITERAL_16(bin3, bin4))




/* ========================================================================= *
 * Swap macro                                                                *
 * ========================================================================= */
#define SWAP(type, a, b) \
  __DO__ { \
    type __tmp_swap_var__ = *(a); \
    *(a) = *(b); \
    *(b) = __tmp_swap_var__; \
  } __WHILE_ZERO__

#ifdef __GNUC__
#  define G_SWAP(a, b) \
  ({ \
    typeof(*(a)) __tmp_swap_var__ = *(a); \
    *(a) = *(b); \
    *(b) = __tmp_swap_var__; \
  })
#endif

#define I_SWAP(a, b) \
  ( \
    *(a) ^= *(b), \
    *(b) ^= *(a), \
    *(a) ^= *(b) \
  )

#define F_SWAP(a, b) \
  ( \
    *(a) += *(b), \
    *(b)  = *(a) - *(b), \
    *(a) -= *(b) \
  )

#define SI_SWAP(a, b) \
  (((a) == (b)) ? 0 : \
    ( \
      *(a) ^= *(b), \
      *(b) ^= *(a), \
      *(a) ^= *(b), \
      1 \
    ) \
  )

#define SF_SWAP(a, b) \
  (((a) == (b)) ? 0 : \
    ( \
      *(a) += *(b), \
      *(b)  = *(a) - *(b), \
      *(a) -= *(b), \
      1 \
    ) \
  )

#define WI_SWAP(a, b) \
  (*(a) ^= *(b) ^= *(a) ^= *(b))

#define WF_SWAP(a, b) \
  (*(a) += *(b) -= *(a) = *(b) - *(a))

#define WSI_SWAP(a, b) \
  (((a) != (b)) && (*(a) ^= *(b) ^= *(a) ^= *(b), 1))

#define WSF_SWAP(a, b)  \
  (((a) != (b)) && (*(a) += *(b) -= *(a) = *(b) - *(a), 1))


#define $DUFFS_LOOP(n, STATEMENT, ...) \
  __DO__ { \
    int __tmp_loop_var__ = ((n) + 7) >> 3; \
    switch ((n) & 7) { \
      case 0: do { STATEMENT; __VA_ARGS__; \
      case 7:      STATEMENT; __VA_ARGS__; \
      case 6:      STATEMENT; __VA_ARGS__; \
      case 5:      STATEMENT; __VA_ARGS__; \
      case 4:      STATEMENT; __VA_ARGS__; \
      case 3:      STATEMENT; __VA_ARGS__; \
      case 2:      STATEMENT; __VA_ARGS__; \
      case 1:      STATEMENT; __VA_ARGS__; \
              } while (--__tmp_loop_var__); \
    } \
  } __WHILE_ZERO__


#if defined(__cplusplus)
#  define LAMBDA(rettype, ARG_LIST, BODY) \
     ([&]ARG_LIST -> rettype { BODY; } )
#elif defined(__GNUC__) && !defined(__clang__)
#  define LAMBDA(rettype, ARG_LIST, BODY) \
   ({ \
     rettype __lambda_funcion__ ARG_LIST { BODY; } \
     __lambda_funcion__; \
   })
#endif




/* ========================================================================= *
 * Until and unless                                                          *
 * ========================================================================= */
#define $UNTIL(...)  while (!(__VA_ARGS__))
#define until(...)   $UNTIL (__VA_ARGS__)

#define $UNLESS(...)  if (!(__VA_ARGS__))
#define unless(...)   $UNLESS (__VA_ARGS__)


/* ========================================================================= *
 * Macros about Integer                                                      *
 * ========================================================================= */
#define ABS(a)     ((a) > 0   ? (a) : -(a))
#define MAX(a, b)  ((a) > (b) ? (a) :  (b))
#define MIN(a, b)  ((a) < (b) ? (a) :  (b))
#define SQ(n)      ((n) * (n))

#define MAX2(a, b)  MAX(a, b)
#define MIN2(a, b)  MIN(a, b)

#define MAX3(a, b, c)     ((a) > MAX((b), (c)) ? (a) : MAX((b), (c)))
#define MIN3(a, b, c)     ((a) < MIN((b), (c)) ? (a) : MIN((b), (c)))

#define MAX4(a, b, c, d)  ((a) > MAX3((b), (c), (d)) ? (a) : MAX3((b), (c), (d)))
#define MIN4(a, b, c, d)  ((a) < MIN3((b), (c), (d)) ? (a) : MIN3((b), (c), (d)))




/* ========================================================================= *
 * Macros about bit-calculation                                              *
 * ========================================================================= */
/* Determine given type is sined or unsigned */
#define Iissigned(itype)  ((itype) (-1) < 0)

/* Determine given type is Two's complement representation or not */
#define Iistwos_cmpl(itype) \
  (Iissigned(itype) && \
      ((itype) ((((itype) 1 << (bitsize(itype) - 2)) - 1) << 2) \
    == (itype) (-4)))

/* Determine given type is ones' complement representation or not */
#define Iisones_cmpl(itype) \
  (Iissigned(itype) && \
      ((itype) ((((itype) 1 << (bitsize(itype) - 2)) - 1) << 2) \
    == (itype) (-3)))

/* Determine given type has signed bit and absolute value or not */
#define Iissign_abs(itype) \
  (Iissigned(itype) && \
      ((itype) ((((itype) 1 << (bitsize(itype) - 2)) + 1) << 1) \
     == (itype)(-2)))

/* Get the minimum value of given type */
#define Imin(itype) \
  (Iissigned(itype) \
    ? (itype) ((itype) 1 << (bitsize(itype) - 1)) : (itype) 0)

/* Get the maximum value of given type */
#define Imax(itype) \
  (Iissigned(itype) \
    ? (itype) ~((itype) 1 << (bitsize(itype) - 1)) : (itype) ~((itype) 0))

#define idiv_floor(dividend, divisor) \
  ((dividend) / (divisor))

#define idiv_ceil(dividend, divisor) \
  (((dividend) + ((divisor) - 1)) / (divisor))

#define idiv_round(dividend, divisor) \
  ((((dividend) << 1) + divisor) / ((divisor) << 1))




/* ========================================================================= *
 * Macros for macros                                                         *
 * ========================================================================= */
/* Stringify argument */
#define M_STR(arg)           #arg
/* Expand macro and stringify it */
#define MACRO_TOSTRING(arg)  M_STR(arg)


#endif  /* UTIL_H */
