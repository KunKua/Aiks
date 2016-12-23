/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef AK_MATH_TRANSFORM_H
#define AK_MATH_TRANSFORM_H

#include <stdio.h>
#include "math/AkMatrix44.h"

namespace aiks {

    class Transform
	{
    public:
        Transform();
        ~Transform();
        
        Vec4 operator*(Vec4 vector);
        Transform * operator*=(Transform &t);
        
        static Transform * translate(const Vec3 &vector);
        static Transform * scale(const Vec3 &vector);
        static Transform * rotate(const Vec3 &vector);
        static Transform * rotate(const float angleX, const float angleY, const float angleZ);
        
        static Transform * perspective(float fov, float clipNear, float clipFar);
        static Transform * perspective(float fovy, float aspect, float zn, float zf);
        static Transform * perspective(float N);
        static Transform * lookAt(const SHPoint3D &cameraPos, const Vec3 &directionVector);
        
        Matrix44 *m;
    private:
        
    };
}

#endif /* AkTransform_h */
