/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * ********************************************/

#ifndef AK_MATH_POINT_H
#define AK_MATH_POINT_H

#include "base/AkTypes.h"

namespace aiks {

typedef struct _Point
{
	s32 x;
	s32 y;
}Point;

typedef struct _PointF{
    f32 x;
    f32 y;
}PointF;

typedef struct _UVCoorF{
    f32 u;
    f32 v;
}UVCoorF;

typedef struct _Point3D{
    f32 x;
    f32 y;
    f32 z;
}Point3D;

typedef struct _Triangle{
    PointF a;
    PointF b;
    PointF c;
}Triangle;

typedef struct _Triangle3D{
    Point3D a;
    Point3D b;
    Point3D c;
}_Triangle3D;

typedef struct _SimpleTri{
    u32 a;
    u32 b;
    u32 c;
}SimpleTri;

typedef struct _Rect{
    s32 x;
    s32 y;
    s32 w;
    s32 h;
}Rect;

typedef struct _Vector3D{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
}Vector3D;

static inline Point PointMake(int x, int y){
    return (Point){x, y};
}

static inline PointF PointFMake(float x, float y){
    return (PointF){x, y};
}

static inline Point3D Point3DMake(float x, float y, float z){
    return (Point3D){x, y, z};
}

static inline Rect RectMake(int x, int y, int w, int h){
    return (Rect){x, y, w, h};
}

static inline SHVector3D SHVector3DMake(float x, float y, float z, float w){
    return (SHVector3D){x, y, z, w};
}

static inline SHVector3D SHVector3DPlus(const SHVector3D &a, const SHVector3D &b){
    SHVector3D result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = 1.0F;
    
    return result;
}

}

#endif
