/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef FakeLight_hpp
#define FakeLight_hpp

#include <stdio.h>
#include "light/ILight.h"
#include "math/BasicGeometry.h"

namespace sh{
    class FakeLight : public ILight{
    public:
        FakeLight(float m);
        ~FakeLight();
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

#endif /* FakeLight_hpp */
