/*************************************
 * Copyright 2016 Aiks Group
 * ***********************************/

#ifndef AIKS_BASE_TYPES_H
#define AIKS_BASE_TYPES_H

#include <stddef.h>
#include <stdint.h>

#include <string.h>

typedef int8_t  Int8
typedef int16_t Int16
typedef int32_t Int32
typedef int64_t Int64
typedef uint8_t uInt8
typedef uint16_t uInt16
typedef uint32_t uInt32
typedef uint64_t uInt64

template <typename T> inline void AkSwap(T& a,T& b)
{
		T c(a);
		a = b;
		b = c;
}

static inline Int32 AkMax32(Int32 a, Int32 b) {
    if (a < b)
        a = b;
    return a;
}

static inline Int32 AkMin32(Int32 a, Int32 b) {
    if (a > b)
        a = b;
    return a;
}

template <typename T> const T& AkMin(const T& a, const T& b) {
    return (a < b) ? a : b;
}

template <typename T> const T& AkMax(const T& a, const T& b) {
    return (b < a) ? a : b;
}

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
