/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * ********************************************/

#ifndef AK_MATH_VECTOR2_H
#define AK_MATH_VECTOR2_H

const float VEC_EPSILON = 0.05f;

namespace aiks {

template<typename F> class TVec2
{
public:
	F _x,_y;
	
	inline TVec2(){};
	inline TVec2(F vx, F vy) {_x = vx; _y = vy};
	explicit inline TVec2(F m) { _x = _y = m; }

	inline TVec2& set(F x,F y) { _x = F(x); _y = F(y); return *this;}

	template<class F1> inline TVec2(const TVec2<F1>& src) { _x = F(src._x); _y = F(src._y); }
	template<class F1> inline explicit TVec2(const F1* psrc) { _x = F(psrc[0]); _y = F(psrc[1]); }

	inline TVec2& operator=(const TVec2& src) { _x = src._x; _y = src._y; return *this; }
	
	inline F getLength() const
	{
			return sqrt(_x * _x + _y * _y);
	}

	TVec2& normalize()
	{
		F invLen = sqrt(_x * _x + _y * _y);
		_x *= invLen;
		_y *= invLen;
		return *this;
	}

	inline F&        operator[](int idx)       { return *((F*)&_x + idx); }
	inline F         operator[](int idx) const { return *((F*)&_x + idx); }
	inline           operator F*()             { return &_x; }
	inline TVec2& flip()                    { _x = -_x; _y = -_y; return *this; }
	inline TVec2& zero()                    { _x = _y = 0; return *this; }
	inline TVec2  rot90ccw() const          { return TVec2(-_y, _x); }
	inline TVec2  rot90cw() const           { return TVec2(_y, -_x); }
};	


typedef TVec2<f32> Vec2;
typedef TVec2<F64> Vec2d; //<< 64 bit double type

}

#endif
