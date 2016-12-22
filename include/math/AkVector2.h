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
};	


typedef TVec2<f32> Vec2;

}

#endif
