/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * ********************************************/

#ifndef AK_MATH_QUAT_H
#define AK_MATH_QUAT_H

#include "base/AkTypes.h"
#include "math/AkMath.h"

const float RAD_EPSILON = 0.01f;

namespace aika {

template<typename F>
class TQuaternion
{
public:
	TVec3<F> _v;
	F		 _w;

	//! ASSIGNMENT OPERATOR of identical Quat types.
	//! The assignment operator has precedence over assignment constructor.
	//! Quat q; q=q0;
	ILINE TQuaternion<F>& operator=(const TQuaternion<F>& src)
	{
		_v._x = src._v._x;
		_v._y = src._v._y;
		_v._z = src._v._z;
		_w = src._w;
		return *this;
	}

	//! CONSTRUCTOR to initialize a Quat from 4 floats.
	//! Quaternion q(1,0,0,0);
	ILINE TQuaternion<F>(F qw, F qx, F qy, F qz)
	{
		_w = qw;
		_v._x = qx;
		_v._y = qy;
		_v._z = qz;
	}
	//! CONSTRUCTOR to initialize a Quat with a scalar and a vector.
	//! Quat q(1,Vec3(0,0,0));
	ILINE TQuaternion<F>(F scalar, const TVec3<F> &vector)
	{
		_v = vector;
		_w = scalar;
	};
}

}


//!<<Quaternion
