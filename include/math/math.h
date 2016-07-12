//
//  math.h
//  Aiks_lib
//
//  Created by 7heaven on 16/7/12.
//  Copyright © 2016年 Saint Hsu. All rights reserved.
//

#ifndef math_h
#define math_h

#include "math/BasicGeometry.h"

inline SHVector3D crossProduct(SHVector3D v0, SHVector3D v1){
    SHVector3D result;
    
    result.x = v0.y * v1.z - v0.z * v1.y;
    result.y = v0.z * v1.x - v0.x * v1.z;
    result.z = v0.x * v1.y - v0.y * v1.x;
    result.w = 1.0F;
    
    return result;
}

inline SHVector3D plus(SHVector3D v0, SHVector3D v1){
    SHVector3D result;
    result.x = v0.x + v1.x;
    result.y = v0.y + v1.y;
    result.z = v0.z + v1.z;
    result.w = 1.0F;
    
    return result;
}

#endif /* math_h */
