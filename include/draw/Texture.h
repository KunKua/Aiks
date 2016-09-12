//
//  Texture.hpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/16.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include "math/BasicGeometry.h"

namespace sh{
    
    enum FilterType{
        None,
        Bilinear,
        Trilinear,
        Anisotropic
    };
    
    class Texture{
    public:
        
        virtual void setFilterType(FilterType type) = 0;
        virtual FilterType getFilterType() = 0;
        
        virtual SHColor getPixel(unsigned int x, unsigned int y) = 0;
        virtual SHColor getPixelF(float u, float v) = 0;
        
        unsigned int width;
        unsigned int height;
    protected:
        FilterType type;
    };
}

#endif /* Texture_hpp */
