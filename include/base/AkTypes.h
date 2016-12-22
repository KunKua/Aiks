/*************************************
 * Copyright 2016 Aiks Group
 * ***********************************/

#ifndef AIKS_BASE_TYPES_H
#define AIKS_BASE_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "base/AkAssert.h"

/// The maximum value of a u64.
#define U64_MAX	UINT64_MAX

/// would be nice if newlib had this already
#ifndef SSIZE_MAX
#ifdef SIZE_MAX
#define SSIZE_MAX ((SIZE_MAX) >> 1)
#endif
#endif

typedef uint8_t u8;   ///<  8-bit unsigned integer
typedef uint16_t u16; ///< 16-bit unsigned integer
typedef uint32_t u32; ///< 32-bit unsigned integer
typedef uint64_t u64; ///< 64-bit unsigned integer

typedef int8_t s8;   ///<  8-bit signed integer
typedef int16_t s16; ///< 16-bit signed integer
typedef int32_t s32; ///< 32-bit signed integer
typedef int64_t s64; ///< 64-bit signed integer

typedef volatile u8 vu8;   ///<  8-bit volatile unsigned integer.
typedef volatile u16 vu16; ///< 16-bit volatile unsigned integer.
typedef volatile u32 vu32; ///< 32-bit volatile unsigned integer.
typedef volatile u64 vu64; ///< 64-bit volatile unsigned integer.

typedef volatile s8 vs8;   ///<  8-bit volatile signed integer.
typedef volatile s16 vs16; ///< 16-bit volatile signed integer.
typedef volatile s32 vs32; ///< 32-bit volatile signed integer.
typedef volatile s64 vs64; ///< 64-bit volatile signed integer.

typedef float  f32; //< 32 bit float
typedef double f64; //< 64 bit float
COMPILE_TIME_ASSERT(sizeof(f32) == 4);
COMPILE_TIME_ASSERT(sizeof(f64) == 8);


typedef void (*ThreadFunc)(void *); ///< Thread entrypoint function.
typedef void (*voidfn)(void);

/// Creates a bitmask from a bit number.
#define BIT(n) (1U<<(n))

/// Aligns a struct (and other types?) to m, making sure that the size of the struct is a multiple of m.
#define ALIGN(m)   __attribute__((aligned(m)))
/// Packs a struct (and other types?) so it won't include padding bytes.
#define PACKED     __attribute__((packed))

#ifndef LIBCTRU_NO_DEPRECATION
/// Flags a function as deprecated.
#define DEPRECATED __attribute__ ((deprecated))
#else
/// Flags a function as deprecated.
#define DEPRECATED

#define AkAlign2(x)     (((x) + 1) >> 1 << 1)
#define AkIsAlign2(x)   (0 == ((x) & 1))

#define AkAlign4(x)     (((x) + 3) >> 2 << 2)
#define AkIsAlign4(x)   (0 == ((x) & 3))

#define AkAlign8(x)     (((x) + 7) >> 3 << 3)
#define AkIsAlign8(x)   (0 == ((x) & 7))

#define AkAlign16(x)     (((x) + 15) >> 4 << 4)
#define AkIsAlign16(x)   (0 == ((x) & 15))

#define AkAlignPtr(x)   (sizeof(void*) == 8 ?   AkAlign8(x) :   AkAlign4(x))
#define AkIsAlignPtr(x) (sizeof(void*) == 8 ? AkIsAlign8(x) : AkIsAlign4(x))

#define MakeNonCopyable(TypeName) \
		TypeName(const TypeName&);\
		TypeName& operator=(const TypeName&) \

class NonCopyable
{
public:
		NonCopyable() {}
private:
		MakeNonCopyable(NonCopyable);
}

#endif
