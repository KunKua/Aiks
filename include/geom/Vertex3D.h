//
//  Vertex3D.hpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/14.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef Vertex3D_hpp
#define Vertex3D_hpp

#include <stdio.h>
#include "math/BasicGeometry.h"

namespace sh{
    class Vertex3D{
    public:
        Vertex3D();
        ~Vertex3D();
        
        SHVector3D pos;
        SHVector3D normal;
        float normal_m;
        
        float u;
        float v;
        
        SHPoint screenPos;
        
    };
}

#endif /* Vertex3D_hpp */
