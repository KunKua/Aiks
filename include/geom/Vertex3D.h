//
//  Vertex3D.h
//
//  Created by 7heaven on 16/5/14.
//  Copyright © 2016年 Aiks Group. All rights reserved.
//

#ifndef AK_GEOM_VERTEX3D_H
#define AK_GEOM_VERTEX3D_H

#include <stdio.h>
#include "math/BasicGeometry.h"

namespace aiks{

class Vertex3D
{
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

#endif /* AkVertex3D_h*/
