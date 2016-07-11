//
//  IMaterial.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/18.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef IMaterial_h
#define IMaterial_h

#include "math/BasicGeometry.h"

namespace sh{
    class IMaterial{
    public:
        virtual SHColor compute(SHVector3D input, SHVector3D output) = 0;
    };
}

#endif /* IMaterial_h */
