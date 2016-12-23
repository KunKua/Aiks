/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef AK_DRAW_TEXTURE_H
#define AK_DRAW_TEXTURE_H

#include <stdio.h>
#include "math/BasicGeometry.h"

namespace aiks {
    
    enum FilterType{
        None,
        Bilinear,
        Trilinear,
        Anisotropic
    };
    
    class Texture
	{
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
