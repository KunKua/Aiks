/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef SimpleDiffuseLight_hpp
#define SimpleDiffuseLight_hpp

#include <stdio.h>
#include "light/ILight.h"

namespace sh{
    class SimpleDiffuseLight: public ILight{
    public:
        SimpleDiffuseLight(float m);
        ~SimpleDiffuseLight();
        SHColor compute(SHColor inputPixelColor, float input_m);
        SHColor compute(SHColor inputPixelColor);
        SHColor compute(const Vertex3D &a,
                        const Vertex3D &b,
                        const Vertex3D &c,
                        SHColor inputPixelColor);
    private:
        float m;
    };
}

#endif /* SimpleDiffuseLight_hpp */
