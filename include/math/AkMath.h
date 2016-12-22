//
//  math.h
//
//  Created by 7heaven on 16/7/12.
//  Copyright © 2016年 Aiks Group. All rights reserved.
//

#ifndef AK_MATH_MATH_H
#define AK_MATH_MATH_H

#include <float.h>
#include <math.h>

#include "base/AkTypes.h"

#if defined(DEBUG)
	#define AK_MATH_ASSERT(x)
#else
	#define AK_MATH_ASSERT(x)
#endif

// Definitions
const f32 PI32 = f32(3.14159265358979323846264338327950288419716939937510);
const f64 PI64 = 3.14159265358979323846264338327950288419716939937510;       //!< pi

const f32 2PI32 = f32(3.14159265358979323846264338327950288419716939937510 * 2.0);
const f64 2PI64 = 3.14159265358979323846264338327950288419716939937510 * 2.0; //!< 2*pi

const f32 ln2 = 0.69314718055994530941723212145818f;       //!< ln(2)

const f64 sqrt2 = 1.4142135623730950488016887242097;
const f64 sqrt3 = 1.7320508075688772935274463415059;

#define DEG2RAD(a) ((a) * (PI32 / 180.0f))
#define RAD2DEG(a) ((a) * (180.0f / PI32))

// MIN and MAX macros are sometimes needed for constant definitions
#ifndef MAX
	#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
	#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

// Define min and max as proper template
#ifdef min
	#undef min
#endif

#ifdef max
	#undef max
#endif

template<typename T> inline T   min(T a, T b)   { return b < a ? b : a; }
template<typename T> inline T   max(T a, T b)   { return a < b ? b : a; }
template<typename T, class _Compare> inline T min(T a, T b, _Compare comp) { return comp(b, a) ? b : a; }
template<typename T, class _Compare> inline T max(T a, T b, _Compare comp) { return comp(a, b) ? b : a; }

inline s32 iszero(f32 x)
{
	union
	{
		f32   f;
		s32 i;
	} u;
	u.f = x;
	u.i &= 0x7FFFFFFF;
	return -(u.i >> 31 ^ (u.i - 1) >> 31);
}
inline s32 iszero(f64 x)
{
	union
	{
		f32   f;
		s32 i;
	} u;
	u.f = (f32)x;
	u.i &= 0x7FFFFFFF;
	return -((u.i >> 31) ^ (u.i - 1) >> 31);
}
inline s32 iszero(s32 x)   { return -(x >> 31 ^ (x - 1) >> 31); }
#if AK_PLATFORM_64BIT && !defined(__clang__)
inline s64 iszero(__int64 x) { return -(x >> 63 ^ (x - 1) >> 63); }
#endif
#if AK_PLATFORM_64BIT && defined(__clang__) && !AK_PLATFORM_LINUX && !AK_PLATFORM_ANDROID
inline s64 iszero(int64_t x) { return -(x >> 63 ^ (x - 1) >> 63); }
#endif
#if AK_PLATFORM_64BIT && (AK_PLATFORM_LINUX || AK_PLATFORM_ANDROID || AK_PLATFORM_APPLE)
inline s64 iszero(long int x) { return -(x >> 63 ^ (x - 1) >> 63); }
#endif

inline Vector3D crossProduct(SHVector3D v0, SHVector3D v1){
    SHVector3D result;
    
    result.x = v0.y * v1.z - v0.z * v1.y;
    result.y = v0.z * v1.x - v0.x * v1.z;
    result.z = v0.x * v1.y - v0.y * v1.x;
    result.w = 1.0F;
    
    return result;
}

inline Vector3D plus(SHVector3D v0, SHVector3D v1){
    SHVector3D result;
    result.x = v0.x + v1.x;
    result.y = v0.y + v1.y;
    result.z = v0.z + v1.z;
    result.w = 1.0F;
    
    return result;
}

#endif /* AkMath_h */
