/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * ********************************************/

#ifndef AK_MATH_VECTOR3_H
#define AK_MATH_VECTOR3_H

const float VEC_EPSILON = 0.05f;

namespace aiks {

template<typename F> class TVec3
{
public:
	F _x,_y,_z;
	
	inline TVec3(){};
	inline TVec3(F vx, F vy, F vz) {_x = vx; _y = vy; _z = vz};
	explicit inline TVec3(F m) { _x = _y = _z = m; }

	inline TVec3& set(F x, F y, F z) { _x = F(x); _y = F(y); _z = F(z); return *this;}

	template<class F1> inline TVec3(const TVec3<F1>& src) { _x = F(src._x); _y = F(src._y); _z = F(src._z)}
	template<class F1> inline explicit TVec3(const F1* psrc) { _x = F(psrc[0]); _y = F(psrc[1]); _z = F(psrc[2]); }

	inline TVec3& operator=(const TVec3& src) { _x = src._x; _y = src._y; _z = src._z; return *this; }
	
	inline F getLength() const
	{
			return sqrt(_x * _x + _y * _y + _z * _z);
	}

	TVec3& normalize()
	{
		F invLen = sqrt(_x * _x + _y * _y + _z * _z);
		_x *= invLen;
		_y *= invLen;
		_z *= invLen;
		return *this;
	}
};	


typedef TVec3<f32> Vec3;
typedef TVec3<F64> Vec3d; //<< 64 bit double type

}

#endif
