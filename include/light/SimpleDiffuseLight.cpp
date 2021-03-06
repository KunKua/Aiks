/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#include "light/SimpleDiffuseLight.h"

namespace sh {
    SimpleDiffuseLight::SimpleDiffuseLight(float m){
        this->m = m;
    }
    
    SimpleDiffuseLight::~SimpleDiffuseLight(){
    }
    
    SHColor SimpleDiffuseLight::compute(SHColor inputPixelColor, float input_m){
        float tmp_m = this->m;
        this->m = input_m;
        
        SHColor result = compute(inputPixelColor);
        
        this->m = tmp_m;
        
        return result;
    }
    
    SHColor SimpleDiffuseLight::compute(SHColor inputPixelColor){
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        
        float ra = (1.0 - m) + 0.4;
        int preR = (int) (ra * inputPixelColor.r);
        int preG = (int) (ra * inputPixelColor.g);
        int preB = (int) (ra * inputPixelColor.b);
        
        if(preR > 0xFF) preR = 0xFF;
        if(preG > 0xFF) preG = 0xFF;
        if(preB > 0xFF) preB = 0xFF;
        
        red = preR;
        green = preG;
        blue = preB;
        
        return SHColorMake(0xFF000000 | red << 16 | green << 8 | blue);
    }
    
    SHColor SimpleDiffuseLight::compute(const sh::Vertex3D &a, const sh::Vertex3D &b, const sh::Vertex3D &c, SHColor inputPixelColor){
        return SHColorMake(0);
    }
}
