/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * ********************************************/

#ifndef AK_MATH_VECTOR3_H
#define AK_MATH_VECTOR3_H

const float VEC_EPSILON = 0.05f;

namespace aiks {

template<typename F> class TVec4
{
public:
	F _x,_y,_z,_w;
	
	inline TVec4(){};
	inline TVec4(F vx, F vy, F vz, F vw) {_x = vx; _y = vy; _z = vz; _w = vw;};
	explicit inline TVec4(F m) { _x = _y = _z = _w = m; }

	inline TVec4& set(F x, F y, F z, F w) { _x = F(x); _y = F(y); _z = F(z); _w = F(w); return *this;}

	template<class F1> inline TVec4(const TVec4<F1>& src) { _x = F(src._x); _y = F(src._y); _z = F(src._z); _w = F(src._w);}
	template<class F1> inline explicit TVec4(const F1* psrc) { _x = F(psrc[0]); _y = F(psrc[1]); _z = F(psrc[2]); _w = F(psrc[3]); }

	inline TVec4& operator=(const TVec4& src) { _x = src._x; _y = src._y; _z = src._z; _w = src._w; return *this; }
	
	inline F getLength() const
	{
			return sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
	}

	TVec4& normalize()
	{
		F invLen = sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
		_x *= invLen;
		_y *= invLen;
		_z *= invLen;
		return *this;
	}


};	


typedef TVec4<f32> Vec4;
typedef TVec4<F64> Vec4d; //<< 64 bit double type

//! Vector addition.
template<class F1, class F2>
inline TVec4<F1> operator+(const TVec4<F1>& v0, const TVec4<F2>& v1)
{
	return TVec4<F1>(v0._x + v1._x, v0._y + v1._y, v0._z + v1._z, v0._w + v1._w);
}
//! Vector subtraction.
template<class F1, class F2>
inline TVec4<F1> operator-(const TVec4<F1>& v0, const TVec4<F2>& v1)
{
	return TVec4<F1>(v0._x - v1._x, v0._y - v1._y, v0._z - v1._z, v0._w - v1._w);
}

//! Vector multiplication.
template<class F1, class F2>
inline TVec4<F1> operator*(const TVec4<F1> v0, const TVec4<F2>& v1)
{
	return TVec4<F1>(v0._x * v1._x, v0._y * v1._y, v0._z * v1._z, v0._w * v1._w);
}

//! Vector division.
template<class F1, class F2>
inline TVec4<F1> operator/(const TVec4<F1>& v0, const TVec4<F2>& v1)
{
	return TVec4<F1>(v0._x / v1._x, v0._y / v1._y, v0._z / v1._z, v0._w / v1._w);
}

}

#endif
