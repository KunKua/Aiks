//
//  ColorTexture.cpp
//  Aiks_lib
//
//  Created by 7heaven on 16/9/12.
//  Copyright © 2016年 Saint Hsu. All rights reserved.
//

#include "ColorTexture.h"

namespace sh{
    ColorTexture::ColorTexture(SHColor solidColor)
    :solidColor(solidColor){
        
    }
    
    FilterType ColorTexture::getFilterType(){
        return FilterType::None;
    }
    
    void ColorTexture::setFilterType(sh::FilterType type){
        
    }
    
    SHColor ColorTexture::getPixelF(float u, float v){
        return this->solidColor;
    }
    
    SHColor ColorTexture::getPixel(unsigned int u, unsigned int v){
        return this->solidColor;
    }
}