/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef ILight_h
#define ILight_h

#include "math/BasicGeometry.h"
#include "geom/Vertex3D.h"

namespace sh{
    class ILight{
    public:
        ~ILight(){}
        virtual SHColor compute(SHColor inputPixelColor, float input_m) = 0;
        virtual SHColor compute(SHColor inputPixelColor) = 0;
        virtual SHColor compute(const Vertex3D &a,
                                const Vertex3D &b,
                                const Vertex3D &c,
                                SHColor inputPixelColor) = 0;
    };
}



#endif /* ILight_h */
