/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef AK_MATH_COLOR_H
#define AK_MATH_COLOR_H

#include "base/AkTypes.h"
#include "math/AkMath.h"

namespace aiks {

float AkClampf(f32 x, f32 min, float max)
{
		return x < min? min : x < max ? x : max;
}

template<class T> class TColor;

typedef TColor<u8> ColorB;//[0,255]
typedef TColor<f32> ColorF;//[0.0,1.0]

template<class T>
class TColor
{
public:
	T _r,_g,_b,_a;

	inline TColor() {};
	inline TColor(T x,T y,T z);	
	inline TColor(T x, T y, T z, T w);

	inline TColor(const u32 abgr);
	inline TColor(const f32 c);
	inline TColor(const ColorF& c);
	inline TColor(const ColorF& c, f32 alpha);
	inline TColor(const Vec3& c, f32 alpha);

	void clamp(f32 min=0, f32 max = 1.0f)
	{
		_r = ::AkClampf(_r, min, max);
		_g = ::AkClampf(_g, min, max);
		_b = ::AkClampf(_b, min, max);
		_a = ::AkClampf(_a, min, max);
	}

	void scale(f32 f)
	{
		_r = static_cast<T>(_r * f);
		_g = static_cast<T>(_g * f);
		_b = static_cast<T>(_b * f);
	}

	float luminance() const
	{
		return _r * 0.30f + _g * 0.59f + _b * 0.11f;		
	}
		
	inline f32 max() const
	{
		return max(_r,max(_b,_g));
	}

	f32 normalize(ColorF& out) const
	{
		f32 max = max();
		if(max == 0)
			return 0;
		out = *this / max;
		return max;
	}

	inline TColor(const Vec3& v)
	{
		_r = (T)v._x;
		_g = (T)v._y;
		_b = (T)v._z;
		_a = (T)1.f;
	}

	inline TColor& operator=(const Vec3& v)      { _r = (T)v._x; _g = (T)v._y; _b = (T)v._z; _a = (T)1.0f; return *this; }
	inline TColor& operator=(const TColor& c) { _r = (T)c._r; _g = (T)c._g; _b = (T)c._b; _a = (T)c._a; return *this; }

	inline T&         operator[](int index)         { AK_MATH_ASSERT(index >= 0 && index <= 3); return ((T*)this)[index]; }
	inline T          operator[](int index) const   { AK_MATH_ASSERT(index >= 0 && index <= 3); return ((T*)this)[index]; }

	inline void set(T x, T y, T z, T w)
	{
		_r = x;
		_g = y;
		_b = z;
		_a = w;
	}

	inline TColor operator+() const
	{
		return *this;
	}

	inline TColor operator-() const
	{
		return TColor<T>(-_r, -_g, -_b, -_a);
	}

	inline TColor& operator+=(const TColor& v)
	{
		T r = _r, g = _g, b = _b, a = _a;
		r += v._r;
		g += v._g;
		b += v._b;
		a += v._a;
		_r = r;
		_g = g;
		_b = b;
		_a = a;
		return *this;
	}
	inline TColor& operator-=(const TColor& v)
	{
		_r -= v._r;
		_g -= v._g;
		_b -= v._b;
		_a -= v._a;
		return *this;
	}
	inline TColor& operator*=(const TColor& v)
	{
		_r *= v._r;
		_g *= v._g;
		_b *= v._b;
		_a *= v._a;
		return *this;
	}
	inline TColor& operator/=(const TColor& v)
	{
		_r /= v._r;
		_g /= v._g;
		_b /= v._b;
		_a /= v._a;
		return *this;
	}
	inline TColor& operator*=(T s)
	{
		_r *= s;
		_g *= s;
		_b *= s;
		_a *= s;
		return *this;
	}

	inline TColor& operator/=(T s)
	{
		s = 1.0f / s;
		_r *= s;
		_g *= s;
		_b *= s;
		_a *= s;
		return *this;
	}

	inline TColor operator+(const TColor& v) const
	{
		return TColor(_r + v._r, _g + v._g, _b + v._b, _a + v._a);
	}

	inline TColor operator-(const TColor& v) const
	{
		return TColor(_r - v._r, _g - v._g, _b - v._b, _a - v._a);
	}

	inline TColor operator*(const TColor& v) const
	{
		return TColor(_r * v._r, _g * v._g, _b * v._b, _a * v._a);
	}

	inline TColor operator/(const TColor& v) const
	{
		return TColor(_r / v._r, _g / v._g, _b / v._b, _a / v._a);
	}

	inline TColor operator*(T s) const
	{
		return TColor(_r * s, _g * s, _b * s, _a * s);
	}

	inline TColor operator/(T s) const
	{
		s = 1.0f / s;
		return TColor(_r * s, _g * s, _b * s, _a * s);
	}

	inline bool operator==(const TColor& v) const
	{
		return (_r == v._r) && (_g == v._g) && (_b == v._b) && (_a == v._a);
	}

	inline bool operator!=(const TColor& v) const
	{
		return (_r != v._r) || (_g != v._g) || (_b != v._b) || (_a != v._a);
	}

	inline unsigned char  packRGB332() const;
	inline unsigned short packARGB4444() const;
	inline unsigned short packRGB555() const;
	inline unsigned short packRGB565() const;
	inline unsigned int   packBGR888() const;
	inline unsigned int   packRGB888() const;
	inline unsigned int   packABGR8888() const;
	inline unsigned int   packARGB8888() const;

	inline Vec4          toVec4() const { return Vec4(_r, _g, _b, _a); }
	inline Vec3          toVec3() const { return Vec3(_r, _g, _b); }

	inline void          toHSV(f32& h, f32& s, f32& v) const;
	inline void          fromHSV(f32 h, f32 s, f32 v);

	inline void          clamp(T bottom = 0.0f, T top = 1.0f);

	inline void          maximum(const TColor<T>& ca, const TColor<T>& cb);
	inline void          minimum(const TColor<T>& ca, const TColor<T>& cb);
	inline void          abs();

	inline void          adjustContrast(T c);
	inline void          adjustSaturation(T s);
	inline void          adjustLuminance(float newLum);

	inline void          lerpFloat(const TColor<T>& ca, const TColor<T>& cb, float s);
	inline void          negative(const TColor<T>& c);
	inline void          grey(const TColor<T>& c);

	//! Helper function - maybe we can improve the integration.
	static inline u32 ComputeAvgCol_Fast(const u32 dwCol0, const u32 dwCol1)
	{
		u32 dwHalfCol0 = (dwCol0 / 2) & 0x7f7f7f7f;      // each component /2
		u32 dwHalfCol1 = (dwCol1 / 2) & 0x7f7f7f7f;      // each component /2

		return dwHalfCol0 + dwHalfCol1;
	}

	//! mCIE: adjusted to compensate problems of DXT compression (extra bit in green channel causes green/purple artifacts).
	TColor<T> RGB2mCIE() const
	{
		TColor<T> in = *this;

		// to get grey chrominance for dark colors
		in._r += 0.000001f;
		in._g += 0.000001f;
		in._b += 0.000001f;

		float RGBSum = in._r + in._g + in._b;

		float fInv = 1.0f / RGBSum;

		float RNorm = 3 * 10.0f / 31.0f * in._r * fInv;
		float GNorm = 3 * 21.0f / 63.0f * in._g * fInv;
		float Scale = RGBSum / 3.0f;

		// test grey
		//	out.r = 10.0f/31.0f;		// 1/3 = 10/30      Red range     0..30, 31 unused
		//	out.g = 21.0f/63.0f;		// 1/3 = 21/63      Green range   0..63

		RNorm = max(0.0f, min(1.0f, RNorm));
		GNorm = max(0.0f, min(1.0f, GNorm));

		return TColor<T>(RNorm, GNorm, Scale);
	}

	//! mCIE: adjusted to compensate problems of DXT compression (extra bit in green channel causes green/purple artefacts).
	TColor<T> mCIE2RGB() const
	{
		TColor<T> out = *this;

		float fScale = out._b;       //                  Blue range   0..31

		// test grey
		//	out.r = 10.0f/31.0f;		// 1/3 = 10/30      Red range     0..30, 31 unused
		//	out.g = 21.0f/63.0f;		// 1/3 = 21/63      Green range   0..63

		out._r *= 31.0f / 30.0f;
		out._g *= 63.0f / 63.0f;
		out._b = 0.999f - out._r - out._g;

		float s = 3.0f * fScale;

		out._r *= s;
		out._g *= s;
		out._b *= s;

		out.clamp();

		return out;
	}

	void rgb2srgb()
	{
		T& tmp[3] = {&_r, &_g, &_b};
		for (int i = 0; i < 3; i++)
		{
			T& c = tmp[i];

			if (c < 0.0031308f)
			{
				c = 12.92f * c;
			}
			else
			{
				c = 1.055f * pow(c, 1.0f / 2.4f) - 0.055f;
			}
		}
	}

	void srgb2rgb()
	{
		T& tmp[3] = {&_r, &_g, &_b};		
		for (int i = 0; i < 3; i++)
		{
			T& c = tmp[i];

			if (c <= 0.040448643f)
			{
				c = c / 12.92f;
			}
			else
			{
				c = pow((c + 0.055f) / 1.055f, 2.4f);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// template specialization
///////////////////////////////////////////////

template<>
inline TColor<f32>::TColor(f32 x, f32 y, f32 z, f32 w)
{
	_r = x;
	_g = y;
	_b = z;
	_a = w;
}

template<>
inline TColor<f32>::TColor(f32 x, f32 y, f32 z)
{
	_r = x;
	_g = y;
	_b = z;
	_a = 1.f;
}

template<>
inline TColor<u8>::TColor(u8 x, u8 y, u8 z, u8 w)
{
	_r = x;
	_g = y;
	_b = z;
	_a = w;
}

template<>
inline TColor<u8>::TColor(u8 x, u8 y, u8 z)
{
	_r = x;
	_g = y;
	_b = z;
	_a = 255;
}

//-----------------------------------------------------------------------------

template<>
inline TColor<f32>::TColor(const unsigned int abgr)
{
	_r = (abgr & 0xff) / 255.0f;
	_g = ((abgr >> 8) & 0xff) / 255.0f;
	_b = ((abgr >> 16) & 0xff) / 255.0f;
	_a = ((abgr >> 24) & 0xff) / 255.0f;
}

//! Use this with RGBA8 macro!
template<>
inline TColor<u8>::TColor(const unsigned int c)
{
	*(unsigned int*)(&r) = c;
}

//-----------------------------------------------------------------------------

template<>
inline TColor<f32>::TColor(const float c)
{
	_r = c;
	_g = c;
	_b = c;
	_a = c;
}
template<>
inline TColor<u8>::TColor(const float c)
{
	_r = (u8)(c * 255);
	_g = (u8)(c * 255);
	_b = (u8)(c * 255);
	_a = (u8)(c * 255);
}
//-----------------------------------------------------------------------------

template<>
inline TColor<f32>::TColor(const ColorF& c)
{
	_r = c._r;
	_g = c._g;
	_b = c._b;
	_a = c.-a;
}
template<>
inline TColor<u8>::TColor(const ColorF& c)
{
	_r = (u8)(c._r * 255);
	_g = (u8)(c._g * 255);
	_b = (u8)(c._b * 255);
	_a = (u8)(c._a * 255);
}

template<>
inline TColor<f32>::TColor(const ColorF& c, float fAlpha)
{
	_r = c._r;
	_g = c._g;
	_b = c._b;
	_a = fAlpha;
}

template<>
inline TColor<f32>::TColor(const Vec3& c, float fAlpha)
{
	_r = c._x;
	_g = c._y;
	_b = c._z;
	_a = fAlpha;
}

template<>
inline TColor<u8>::TColor(const ColorF& c, float fAlpha)
{
	_r = (u8)(c._r * 255);
	_g = (u8)(c._g * 255);
	_b = (u8)(c._b * 255);
	_a = (u8)(fAlpha * 255);
}
template<>
inline TColor<u8>::TColor(const Vec3& c, float fAlpha)
{
	_r = (u8)(c._x * 255);
	_g = (u8)(c._y * 255);
	_b = (u8)(c._z * 255);
	_a = (u8)(fAlpha * 255);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// functions implementation
///////////////////////////////////////////////

template<class T>
inline TColor<T> operator*(T s, const TColor<T>& v)
{
	return TColor<T>(v._r * s, v._g * s, v._b * s, v._a * s);
}

///////////////////////////////////////////////
template<class T>
inline unsigned char TColor<T >::packRGB332() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	if (sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)_r;
		cg = (unsigned char)_g;
		cb = (unsigned char)_b;
	}
	else if (sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(_r) >> 8;
		cg = (unsigned short)(_g) >> 8;
		cb = (unsigned short)(_b) >> 8;
	}
	else // float or double
	{
		cr = (unsigned char)(_r * 255.0f);
		cg = (unsigned char)(_g * 255.0f);
		cb = (unsigned char)(_b * 255.0f);
	}
	return ((cr >> 5) << 5) | ((cg >> 5) << 2) | (cb >> 5);
}

///////////////////////////////////////////////
template<class T>
inline unsigned short TColor<T >::packARGB4444() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	unsigned char ca;
	if (sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)_r;
		cg = (unsigned char)_g;
		cb = (unsigned char)_b;
		ca = (unsigned char)_a;
	}
	else if (sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(_r) >> 8;
		cg = (unsigned short)(_g) >> 8;
		cb = (unsigned short)(_b) >> 8;
		ca = (unsigned short)(_a) >> 8;
	}
	else // float or double
	{
		cr = (unsigned char)(_r * 255.0f);
		cg = (unsigned char)(_g * 255.0f);
		cb = (unsigned char)(_b * 255.0f);
		ca = (unsigned char)(_a * 255.0f);
	}
	return ((ca >> 4) << 12) | ((cr >> 4) << 8) | ((cg >> 4) << 4) | (cb >> 4);
}

///////////////////////////////////////////////
template<class T>
inline unsigned short TColor<T >::packRGB555() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	if (sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)_r;
		cg = (unsigned char)_g;
		cb = (unsigned char)_b;
	}
	else if (sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(_r) >> 8;
		cg = (unsigned short)(_g) >> 8;
		cb = (unsigned short)(_b) >> 8;
	}
	else // float or double
	{
		cr = (unsigned char)(_r * 255.0f);
		cg = (unsigned char)(_g * 255.0f);
		cb = (unsigned char)(_b * 255.0f);
	}
	return ((cr >> 3) << 10) | ((cg >> 3) << 5) | (cb >> 3);
}

///////////////////////////////////////////////
template<class T>
inline unsigned short TColor<T >::packRGB565() const
{
	unsigned short cr;
	unsigned short cg;
	unsigned short cb;
	if (sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned short)_r;
		cg = (unsigned short)_g;
		cb = (unsigned short)_b;
	}
	else if (sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(_r) >> 8;
		cg = (unsigned short)(_g) >> 8;
		cb = (unsigned short)(_b) >> 8;
	}
	else // float or double
	{
		cr = (unsigned short)(_r * 255.0f);
		cg = (unsigned short)(_g * 255.0f);
		cb = (unsigned short)(_b * 255.0f);
	}
	return ((cr >> 3) << 11) | ((cg >> 2) << 5) | (cb >> 3);
}

///////////////////////////////////////////////
template<class T>
inline unsigned int TColor<T >::packBGR888() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	if (sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)_r;
		cg = (unsigned char)_g;
		cb = (unsigned char)_b;
	}
	else if (sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(_r) >> 8;
		cg = (unsigned short)(_g) >> 8;
		cb = (unsigned short)(-b) >> 8;
	}
	else // float or double
	{
		cr = (unsigned char)(_r * 255.0f);
		cg = (unsigned char)(_g * 255.0f);
		cb = (unsigned char)(_b * 255.0f);
	}
	return (cb << 16) | (cg << 8) | cr;
}

///////////////////////////////////////////////
template<class T>
inline unsigned int TColor<T >::packRGB888() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	if (sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)_r;
		cg = (unsigned char)_g;
		cb = (unsigned char)_b;
	}
	else if (sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(_r) >> 8;
		cg = (unsigned short)(_g) >> 8;
		cb = (unsigned short)(_b) >> 8;
	}
	else // float or double
	{
		cr = (unsigned char)(_r * 255.0f);
		cg = (unsigned char)(_g * 255.0f);
		cb = (unsigned char)(_b * 255.0f);
	}
	return (cr << 16) | (cg << 8) | cb;
}

///////////////////////////////////////////////
template<class T>
inline unsigned int TColor<T >::packABGR8888() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	unsigned char ca;
	if (sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)_r;
		cg = (unsigned char)_g;
		cb = (unsigned char)_b;
		ca = (unsigned char)_a;
	}
	else if (sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(_r) >> 8;
		cg = (unsigned short)(_g) >> 8;
		cb = (unsigned short)(_b) >> 8;
		ca = (unsigned short)(_a) >> 8;
	}
	else // float or double
	{
		cr = (unsigned char)(_r * 255.0f);
		cg = (unsigned char)(_g * 255.0f);
		cb = (unsigned char)(_b * 255.0f);
		ca = (unsigned char)(_a * 255.0f);
	}
	return (ca << 24) | (cb << 16) | (cg << 8) | cr;
}

///////////////////////////////////////////////
template<class T>
inline unsigned int TColor<T >::packARGB8888() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	unsigned char ca;
	if (sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)_r;
		cg = (unsigned char)_g;
		cb = (unsigned char)_b;
		ca = (unsigned char)_a;
	}
	else if (sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(_r) >> 8;
		cg = (unsigned short)(_g) >> 8;
		cb = (unsigned short)(_b) >> 8;
		ca = (unsigned short)(_a) >> 8;
	}
	else // float or double
	{
		cr = (unsigned char)(_r * 255.0f);
		cg = (unsigned char)(_g * 255.0f);
		cb = (unsigned char)(_b * 255.0f);
		ca = (unsigned char)(_a * 255.0f);
	}
	return (ca << 24) | (cr << 16) | (cg << 8) | cb;
}

///////////////////////////////////////////////
template<class T>
inline void TColor<T >::toHSV(f32& h, f32& s, f32& v) const
{
	f32 r, g, b;
	if (sizeof(_r) == 1) // 8bit integer
	{
		r = _r * (1.0f / f32(0xff));
		g = _g * (1.0f / f32(0xff));
		b = _b * (1.0f / f32(0xff));
	}
	else if (sizeof(_r) == 2) // 16bit integer
	{
		r = _r * (1.0f / f32(0xffff));
		g = _g * (1.0f / f32(0xffff));
		b = _b * (1.0f / f32(0xffff));
	}
	else // floating point
	{
		r = _r;
		g = _g;
		b = _b;
	}

	if ((b > g) && (b > r))
	{
		if (!::iszero(v = b))
		{
			const f32 min = r < g ? r : g;
			const f32 delta = v - min;
			if (!::iszero(delta))
			{
				s = delta / v;
				h = (240.0f / 360.0f) + (r - g) / delta * (60.0f / 360.0f);
			}
			else
			{
				s = 0.0f;
				h = (240.0f / 360.0f) + (r - g) * (60.0f / 360.0f);
			}
			if (h < 0.0f) h += 1.0f;
		}
		else
		{
			s = 0.0f;
			h = 0.0f;
		}
	}
	else if (g > r)
	{
		if (!::iszero(v = g))
		{
			const f32 min = r < b ? r : b;
			const f32 delta = v - min;
			if (!::iszero(delta))
			{
				s = delta / v;
				h = (120.0f / 360.0f) + (b - r) / delta * (60.0f / 360.0f);
			}
			else
			{
				s = 0.0f;
				h = (120.0f / 360.0f) + (b - r) * (60.0f / 360.0f);
			}
			if (h < 0.0f) h += 1.0f;
		}
		else
		{
			s = 0.0f;
			h = 0.0f;
		}
	}
	else
	{
		if (!::iszero(v = r))
		{
			const f32 min = g < b ? g : b;
			const f32 delta = v - min;
			if (!::iszero(delta))
			{
				s = delta / v;
				h = (g - b) / delta * (60.0f / 360.0f);
			}
			else
			{
				s = 0.0f;
				h = (g - b) * (60.0f / 360.0f);
			}
			if (h < 0.0f) h += 1.0f;
		}
		else
		{
			s = 0.0f;
			h = 0.0f;
		}
	}
}
#pragma warning(push)
#pragma warning(disable:4244)
///////////////////////////////////////////////
template<class T>
inline void TColor<T >::fromHSV(f32 h, f32 s, f32 v)
{
	f32 r, g, b;
	if (::iszero(v))
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
	}
	else if (::iszero(s))
	{
		r = v;
		g = v;
		b = v;
	}
	else
	{
		const f32 hi = h * 6.0f;
		const int32 i = (int32)::floor(hi);
		const f32 f = hi - i;

		const f32 v0 = v * (1.0f - s);
		const f32 v1 = v * (1.0f - s * f);
		const f32 v2 = v * (1.0f - s * (1.0f - f));

		switch (i)
		{
		case 0:
			r = v;
			g = v2;
			b = v0;
			break;
		case 1:
			r = v1;
			g = v;
			b = v0;
			break;
		case 2:
			r = v0;
			g = v;
			b = v2;
			break;
		case 3:
			r = v0;
			g = v1;
			b = v;
			break;
		case 4:
			r = v2;
			g = v0;
			b = v;
			break;
		case 5:
			r = v;
			g = v0;
			b = v1;
			break;

		case 6:
			r = v;
			g = v2;
			b = v0;
			break;
		case -1:
			r = v;
			g = v0;
			b = v1;
			break;
		default:
			r = 0.0f;
			g = 0.0f;
			b = 0.0f;
			break;
		}
	}

	if (sizeof(this->r) == 1) // 8bit integer
	{
		_r = r * f32(0xff);
		_g = g * f32(0xff);
		_b = b * f32(0xff);
	}
	else if (sizeof(this->r) == 2) // 16bit integer
	{
		_r = r * f32(0xffff);
		_g = g * f32(0xffff);
		_b = b * f32(0xffff);
	}
	else // floating point
	{
		_r = r;
		_g = g;
		_b = b;
	}
}
#pragma warning(pop)
///////////////////////////////////////////////
template<class T>
inline void TColor<T >::clamp(T bottom, T top)
{
	_r = min(top, max(bottom, _r));
	_g = min(top, max(bottom, _g));
	_b = min(top, max(bottom, _b));
	_a = min(top, max(bottom, _a));
}

///////////////////////////////////////////////
template<class T>
inline void TColor<T >::maximum(const TColor<T>& ca, const TColor<T>& cb)
{
	_r = max(ca._r, cb._r);
	_g = max(ca._g, cb._g);
	_b = max(ca._b, cb._b);
	_a = max(ca._a, cb._a);
}

///////////////////////////////////////////////
template<class T>
inline void TColor<T >::minimum(const TColor<T>& ca, const TColor<T>& cb)
{
	_r = min(ca._r, cb._r);
	_g = min(ca._g, cb._g);
	_b = min(ca._b, cb._b);
	_a = min(ca._a, cb._a);
}

///////////////////////////////////////////////
template<class T>
inline void TColor<T >::abs()
{
	_r = fabs_tpl(_r);
	_g = fabs_tpl(_g);
	_b = fabs_tpl(-b);
	_a = fabs_tpl(_a);
}

///////////////////////////////////////////////
template<class T>
inline void TColor<T >::adjustContrast(T c)
{
	_r = 0.5f + c * (_r - 0.5f);
	_g = 0.5f + c * (_g - 0.5f);
	_b = 0.5f + c * (_b - 0.5f);
	-a = 0.5f + c * (_a - 0.5f);
}

//! Approximate values for each component's contribution to luminance.
//! Based upon the NTSC standard described in ITU-R Recommendation BT.709.
template<class T>
inline void TColor<T >::adjust_saturation(T s)
{
	T grey = _r * 0.2125f + _g * 0.7154f + _b * 0.0721f;
	_r = grey + s * (_r - grey);
	_g = grey + s * (-g - grey);
	_b = grey + s * (-b - grey);
	-a = grey + s * (_a - grey);
}

//! Optimized yet equivalent version of replacing luminance in XYZ space.
//! Color and luminance are expected to be linear.
template<class T>
inline void TColor<T >::adjustLuminance(float newLum)
{
	TColor<f32> colF(_r, _g, _b, _a);

	float lum = colF._r * 0.212671f + colF._g * 0.715160f + colF._b * 0.072169f;
	if (iszero(lum))
		return;

	*this = TColor<T>(colF * newLum / lum);
}

///////////////////////////////////////////////
template<class T>
inline void TColor<T >::lerpFloat(const TColor<T>& ca, const TColor<T>& cb, float s)
{
	_r = (T)(ca._r + s * (cb._r - ca._r));
	_g = (T)(ca._g + s * (cb._g - ca._g));
	_b = (T)(ca._b + s * (cb._b - ca._b));
	_a = (T)(ca._a + s * (cb._a - ca._a));
}

///////////////////////////////////////////////
template<class T>
inline void TColor<T >::negative(const TColor<T>& c)
{
	_r = T(1.0f) - _r;
	_g = T(1.0f) - _g;
	_b = T(1.0f) - _b;
	_a = T(1.0f) - _a;
}

///////////////////////////////////////////////
template<class T>
inline void TColor<T >::grey(const TColor<T>& c)
{
	T m = (_r + _g + _b) / T(3);

	_r = m;
	_g = m;
	_b = m;
	_a = _a;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//#define RGBA8(r,g,b,a)   (ColorB((u8)(r),(u8)(g),(u8)(b),(u8)(a)))
#if defined(NEED_ENDIAN_SWAP)
	#define RGBA8(a, b, g, r) ((u32)(((u8)(r) | ((uint16)((u8)(g)) << 8)) | (((u32)(u8)(b)) << 16)) | (((u32)(u8)(a)) << 24))
#else
	#define RGBA8(r, g, b, a) ((u32)(((u8)(r) | ((uint16)((u8)(g)) << 8)) | (((u32)(u8)(b)) << 16)) | (((u32)(u8)(a)) << 24))
#endif

#define Col_Black             ColorF(0.000f, 0.000f, 0.000f)                   // 0xFF000000   RGB: 0, 0, 0
#define Col_White             ColorF(1.000f, 1.000f, 1.000f)                   // 0xFFFFFFFF   RGB: 255, 255, 255
#define Col_Aquamarine        ColorF(0.498f, 1.000f, 0.831f)                   // 0xFF7FFFD4   RGB: 127, 255, 212
#define Col_Azure             ColorF(0.000f, 0.498f, 1.000f)                   // 0xFF007FFF   RGB: 0, 127, 255
#define Col_Blue              ColorF(0.000f, 0.000f, 1.000f)                   // 0xFF0000FF   RGB: 0, 0, 255
#define Col_BlueViolet        ColorF(0.541f, 0.169f, 0.886f)                   // 0xFF8A2BE2   RGB: 138, 43, 226
#define Col_Brown             ColorF(0.647f, 0.165f, 0.165f)                   // 0xFFA52A2A   RGB: 165, 42, 42
#define Col_CadetBlue         ColorF(0.373f, 0.620f, 0.627f)                   // 0xFF5F9EA0   RGB: 95, 158, 160
#define Col_Coral             ColorF(1.000f, 0.498f, 0.314f)                   // 0xFFFF7F50   RGB: 255, 127, 80
#define Col_CornflowerBlue    ColorF(0.392f, 0.584f, 0.929f)                   // 0xFF6495ED   RGB: 100, 149, 237
#define Col_Cyan              ColorF(0.000f, 1.000f, 1.000f)                   // 0xFF00FFFF   RGB: 0, 255, 255
#define Col_DarkGray          ColorF(0.663f, 0.663f, 0.663f)                   // 0xFFA9A9A9   RGB: 169, 169, 169
#define Col_DarkGrey          ColorF(0.663f, 0.663f, 0.663f)                   // 0xFFA9A9A9   RGB: 169, 169, 169
#define Col_DarkGreen         ColorF(0.000f, 0.392f, 0.000f)                   // 0xFF006400   RGB: 0, 100, 0
#define Col_DarkOliveGreen    ColorF(0.333f, 0.420f, 0.184f)                   // 0xFF556B2F   RGB: 85, 107, 47
#define Col_DarkOrchid        ColorF(0.600f, 0.196f, 0.800f)                   // 0xFF9932CC   RGB: 153, 50, 204
#define Col_DarkSlateBlue     ColorF(0.282f, 0.239f, 0.545f)                   // 0xFF483D8B   RGB: 72, 61, 139
#define Col_DarkSlateGray     ColorF(0.184f, 0.310f, 0.310f)                   // 0xFF2F4F4F   RGB: 47, 79, 79
#define Col_DarkSlateGrey     ColorF(0.184f, 0.310f, 0.310f)                   // 0xFF2F4F4F   RGB: 47, 79, 79
#define Col_DarkTurquoise     ColorF(0.000f, 0.808f, 0.820f)                   // 0xFF00CED1   RGB: 0, 206, 209
#define Col_DarkWood          ColorF(0.050f, 0.010f, 0.005f)                   // 0xFF0D0301   RGB: 13, 3, 1
#define Col_DeepPink          ColorF(1.000f, 0.078f, 0.576f)                   // 0xFFFF1493   RGB: 255, 20, 147
#define Col_DimGray           ColorF(0.412f, 0.412f, 0.412f)                   // 0xFF696969   RGB: 105, 105, 105
#define Col_DimGrey           ColorF(0.412f, 0.412f, 0.412f)                   // 0xFF696969   RGB: 105, 105, 105
#define Col_FireBrick         ColorF(0.698f, 0.133f, 0.133f)                   // 0xFFB22222   RGB: 178, 34, 34
#define Col_ForestGreen       ColorF(0.133f, 0.545f, 0.133f)                   // 0xFF228B22   RGB: 34, 139, 34
#define Col_Gold              ColorF(1.000f, 0.843f, 0.000f)                   // 0xFFFFD700   RGB: 255, 215, 0
#define Col_Goldenrod         ColorF(0.855f, 0.647f, 0.125f)                   // 0xFFDAA520   RGB: 218, 165, 32
#define Col_Gray              ColorF(0.502f, 0.502f, 0.502f)                   // 0xFF808080   RGB: 128, 128, 128
#define Col_Grey              ColorF(0.502f, 0.502f, 0.502f)                   // 0xFF808080   RGB: 128, 128, 128
#define Col_Green             ColorF(0.000f, 0.502f, 0.000f)                   // 0xFF008000   RGB: 0, 128, 0
#define Col_GreenYellow       ColorF(0.678f, 1.000f, 0.184f)                   // 0xFFADFF2F   RGB: 173, 255, 47
#define Col_IndianRed         ColorF(0.804f, 0.361f, 0.361f)                   // 0xFFCD5C5C   RGB: 205, 92, 92
#define Col_Khaki             ColorF(0.941f, 0.902f, 0.549f)                   // 0xFFF0E68C   RGB: 240, 230, 140
#define Col_LightBlue         ColorF(0.678f, 0.847f, 0.902f)                   // 0xFFADD8E6   RGB: 173, 216, 230
#define Col_LightGray         ColorF(0.827f, 0.827f, 0.827f)                   // 0xFFD3D3D3   RGB: 211, 211, 211
#define Col_LightGrey         ColorF(0.827f, 0.827f, 0.827f)                   // 0xFFD3D3D3   RGB: 211, 211, 211
#define Col_LightSteelBlue    ColorF(0.690f, 0.769f, 0.871f)                   // 0xFFB0C4DE   RGB: 176, 196, 222
#define Col_LightWood         ColorF(0.600f, 0.240f, 0.100f)                   // 0xFF993D1A   RGB: 153, 61, 26
#define Col_Lime              ColorF(0.000f, 1.000f, 0.000f)                   // 0xFF00FF00   RGB: 0, 255, 0
#define Col_LimeGreen         ColorF(0.196f, 0.804f, 0.196f)                   // 0xFF32CD32   RGB: 50, 205, 50
#define Col_Magenta           ColorF(1.000f, 0.000f, 1.000f)                   // 0xFFFF00FF   RGB: 255, 0, 255
#define Col_Maroon            ColorF(0.502f, 0.000f, 0.000f)                   // 0xFF800000   RGB: 128, 0, 0
#define Col_MedianWood        ColorF(0.300f, 0.120f, 0.030f)                   // 0xFF4D1F09   RGB: 77, 31, 9
#define Col_MediumAquamarine  ColorF(0.400f, 0.804f, 0.667f)                   // 0xFF66CDAA   RGB: 102, 205, 170
#define Col_MediumBlue        ColorF(0.000f, 0.000f, 0.804f)                   // 0xFF0000CD   RGB: 0, 0, 205
#define Col_MediumForestGreen ColorF(0.420f, 0.557f, 0.137f)                   // 0xFF6B8E23   RGB: 107, 142, 35
#define Col_MediumGoldenrod   ColorF(0.918f, 0.918f, 0.678f)                   // 0xFFEAEAAD   RGB: 234, 234, 173
#define Col_MediumOrchid      ColorF(0.729f, 0.333f, 0.827f)                   // 0xFFBA55D3   RGB: 186, 85, 211
#define Col_MediumSeaGreen    ColorF(0.235f, 0.702f, 0.443f)                   // 0xFF3CB371   RGB: 60, 179, 113
#define Col_MediumSlateBlue   ColorF(0.482f, 0.408f, 0.933f)                   // 0xFF7B68EE   RGB: 123, 104, 238
#define Col_MediumSpringGreen ColorF(0.000f, 0.980f, 0.604f)                   // 0xFF00FA9A   RGB: 0, 250, 154
#define Col_MediumTurquoise   ColorF(0.282f, 0.820f, 0.800f)                   // 0xFF48D1CC   RGB: 72, 209, 204
#define Col_MediumVioletRed   ColorF(0.780f, 0.082f, 0.522f)                   // 0xFFC71585   RGB: 199, 21, 133
#define Col_MidnightBlue      ColorF(0.098f, 0.098f, 0.439f)                   // 0xFF191970   RGB: 25, 25, 112
#define Col_Navy              ColorF(0.000f, 0.000f, 0.502f)                   // 0xFF000080   RGB: 0, 0, 128
#define Col_NavyBlue          ColorF(0.137f, 0.137f, 0.557f)                   // 0xFF23238E   RGB: 35, 35, 142
#define Col_Orange            ColorF(1.000f, 0.647f, 0.000f)                   // 0xFFFFA500   RGB: 255, 165, 0
#define Col_OrangeRed         ColorF(1.000f, 0.271f, 0.000f)                   // 0xFFFF4500   RGB: 255, 69, 0
#define Col_Orchid            ColorF(0.855f, 0.439f, 0.839f)                   // 0xFFDA70D6   RGB: 218, 112, 214
#define Col_PaleGreen         ColorF(0.596f, 0.984f, 0.596f)                   // 0xFF98FB98   RGB: 152, 251, 152
#define Col_Pink              ColorF(1.000f, 0.753f, 0.796f)                   // 0xFFFFC0CB   RGB: 255, 192, 203
#define Col_Plum              ColorF(0.867f, 0.627f, 0.867f)                   // 0xFFDDA0DD   RGB: 221, 160, 221
#define Col_Red               ColorF(1.000f, 0.000f, 0.000f)                   // 0xFFFF0000   RGB: 255, 0, 0
#define Col_Salmon            ColorF(0.980f, 0.502f, 0.447f)                   // 0xFFFA8072   RGB: 250, 128, 114
#define Col_SeaGreen          ColorF(0.180f, 0.545f, 0.341f)                   // 0xFF2E8B57   RGB: 46, 139, 87
#define Col_Sienna            ColorF(0.627f, 0.322f, 0.176f)                   // 0xFFA0522D   RGB: 160, 82, 45
#define Col_SkyBlue           ColorF(0.529f, 0.808f, 0.922f)                   // 0xFF87CEEB   RGB: 135, 206, 235
#define Col_SlateBlue         ColorF(0.416f, 0.353f, 0.804f)                   // 0xFF6A5ACD   RGB: 106, 90, 205
#define Col_SpringGreen       ColorF(0.000f, 1.000f, 0.498f)                   // 0xFF00FF7F   RGB: 0, 255, 127
#define Col_SteelBlue         ColorF(0.275f, 0.510f, 0.706f)                   // 0xFF4682B4   RGB: 70, 130, 180
#define Col_Tan               ColorF(0.824f, 0.706f, 0.549f)                   // 0xFFD2B48C   RGB: 210, 180, 140
#define Col_Thistle           ColorF(0.847f, 0.749f, 0.847f)                   // 0xFFD8BFD8   RGB: 216, 191, 216
#define Col_Transparent       ColorF(0.0f, 0.0f, 0.0f, 0.0f)                   // 0x00000000   RGB: 0, 0, 0
#define Col_Turquoise         ColorF(0.251f, 0.878f, 0.816f)                   // 0xFF40E0D0   RGB: 64, 224, 208
#define Col_Violet            ColorF(0.933f, 0.510f, 0.933f)                   // 0xFFEE82EE   RGB: 238, 130, 238
#define Col_VioletRed         ColorF(0.800f, 0.196f, 0.600f)                   // 0xFFCC3299   RGB: 204, 50, 153
#define Col_Wheat             ColorF(0.961f, 0.871f, 0.702f)                   // 0xFFF5DEB3   RGB: 245, 222, 179
#define Col_Yellow            ColorF(1.000f, 1.000f, 0.000f)                   // 0xFFFFFF00   RGB: 255, 255, 0
#define Col_YellowGreen       ColorF(0.604f, 0.804f, 0.196f)                   // 0xFF9ACD32   RGB: 154, 205, 50

#define Col_TrackviewDefault  ColorF(0.187820792f, 0.187820792f, 1.0f)

#define Clr_Empty             ColorF(0.0f, 0.0f, 0.0f, 1.0f)
#define Clr_Dark              ColorF(0.15f, 0.15f, 0.15f, 1.0f)
#define Clr_White             ColorF(1.0f, 1.0f, 1.0f, 1.0f)
#define Clr_WhiteTrans        ColorF(1.0f, 1.0f, 1.0f, 0.0f)
#define Clr_Full              ColorF(1.0f, 1.0f, 1.0f, 1.0f)
#define Clr_Neutral           ColorF(1.0f, 1.0f, 1.0f, 1.0f)
#define Clr_Transparent       ColorF(0.0f, 0.0f, 0.0f, 0.0f)
#define Clr_FrontVector       ColorF(0.0f, 0.0f, 0.5f, 1.0f)
#define Clr_Static            ColorF(127.0f / 255.0f, 127.0f / 255.0f, 0.0f, 0.0f)
#define Clr_Median            ColorF(0.5f, 0.5f, 0.5f, 0.0f)
#define Clr_MedianHalf        ColorF(0.5f, 0.5f, 0.5f, 0.5f)
#define Clr_FarPlane          ColorF(1.0f, 0.0f, 0.0f, 0.0f)
#define Clr_FarPlane_R        ColorF(bReverseDepth ? 0.0f : 1.0f, 0.0f, 0.0f, 0.0f)
#define Clr_Unknown           ColorF(0.0f, 0.0f, 0.0f, 0.0f)
#define Clr_Unused            ColorF(0.0f, 0.0f, 0.0f, 0.0f)
#define Clr_Debug             ColorF(1.0f, 0.0f, 0.0f, 1.0f)

}

#endif
