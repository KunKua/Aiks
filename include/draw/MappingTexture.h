/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef MappingTexture_h
#define MappingTexture_h

#include <stdio.h>
#include "Texture.h"

namespace sh{
    class MappingTexture : public Texture{
    public:
        MappingTexture(SHColor *pixels, unsigned int width, unsigned int height);
        ~MappingTexture();
        
        void setFilterType(FilterType type);
        FilterType getFilterType();
        
        SHColor getPixel(unsigned int x, unsigned int y);
        SHColor getPixelF(float u, float v);
    private:
        SHColor mixARGB(SHColor a, SHColor b, float mixedValue);
        SHColor mixRGB(SHColor a, SHColor b, float mixedValue);
# pragma mark TODO
        SHColor mixColors(unsigned int su, unsigned int sv,
                          unsigned int eu, unsigned int ev);
        
        SHColor *pixels;
        
        unsigned int totalSize;
    };
}

#endif /* MappingTexture_h */
