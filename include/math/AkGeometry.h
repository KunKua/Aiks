/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef AK_MATH_GEOMETRY_H
#define AK_MATH_GEOMETRY_H

namespace aiks {

typedef struct SHPoint{
    int x;
    int y;
}SHPoint;

typedef struct SHPointF{
    float x;
    float y;
}SHPointF;

typedef struct SHUVCoorF{
    float u;
    float v;
}SHUVCoorF;

typedef struct SHPoint3D{
    float x;
    float y;
    float z;
}SHPoint3D;

typedef struct SHTriangle{
    SHPointF a;
    SHPointF b;
    SHPointF c;
}SHTriangle;

typedef struct SHTriangle3D{
    SHPoint3D a;
    SHPoint3D b;
    SHPoint3D c;
}SHTriangle3D;

typedef struct SHSimpleTri{
    unsigned int a;
    unsigned int b;
    unsigned int c;
}SHSimpleTri;

struct RectF
{
	float x, y, w, h;
	RectF()
		: x(0), y(0), w(1), h(1)
	{
	}
	AUTO_STRUCT_INFO;
};

struct RectI
{
	int x, y, w, h;
	RectI()
		: x(0), y(0), w(1), h(1)
	{
	}
	RectI(int inX, int inY, int inW, int inH)
		: x(inX), y(inY), w(inW), h(inH)
	{
	}
	inline void Add(RectI rcAdd)
	{
		int x2 = x + w;
		int y2 = y + h;
		int x22 = rcAdd.x + rcAdd.w;
		int y22 = rcAdd.y + rcAdd.h;
		x = min(x, rcAdd.x);
		y = min(y, rcAdd.y);
		x2 = max(x2, x22);
		y2 = max(y2, y22);
		w = x2 - x;
		h = y2 - y;
	}
	inline void Add(int inX, int inY, int inW, int inH)
	{
		Add(RectI(inX, inY, inW, inH));
	}
};

typedef struct SHVector3D{
    float x;
    float y;
    float z;
    float w;
}SHVector3D;

}

#endif /* AkGeometry_h */
