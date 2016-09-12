//
//  ColorTexture.h
//  Aiks_lib
//
//  Created by 7heaven on 16/9/12.
//  Copyright © 2016年 Saint Hsu. All rights reserved.
//

#ifndef ColorTexture_h
#define ColorTexture_h

#include <stdio.h>
#include "Texture.h"

namespace sh{
    class ColorTexture : public Texture{
    public:
        ColorTexture(SHColor solidColor);
        ~ColorTexture();
        
        void setFilterType(FilterType type);
        FilterType getFilterType();
        
        SHColor getPixel(unsigned int x, unsigned int y);
        SHColor getPixelF(float u, float v);
    private:
        SHColor solidColor;
    };
}

#endif /* ColorTexture_h */
