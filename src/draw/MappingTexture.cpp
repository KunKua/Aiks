//
//  MappingTexture.cpp
//  Aiks_lib
//
//  Created by 7heaven on 16/9/12.
//  Copyright © 2016年 Saint Hsu. All rights reserved.
//

#include "MappingTexture.h"
#include <math.h>

namespace sh{
    MappingTexture::MappingTexture(SHColor *pixels, unsigned int width, unsigned int height){
        this->pixels = pixels;
        this->width = width;
        this->height = height;
        
        this->type = FilterType::Bilinear;
        
        this->totalSize = this->width * this->height;
    }
    
    void MappingTexture::setFilterType(sh::FilterType type){
        this->type = type;
    }
    
    FilterType MappingTexture::getFilterType(){
        return this->type;
    }
    
    SHColor MappingTexture::getPixel(unsigned int u, unsigned int v){
        switch(this->type){
            case FilterType::None:{
                int pos = v * this->width + u;
                
                while(pos < 0) pos += this->totalSize;
                while(pos >= this->totalSize) pos -= this->totalSize;
                
                return this->pixels[pos];
            }
                break;
        }
        
        return (SHColor){0};
    }
    
    SHColor MappingTexture::getPixelF(float u, float v){
        switch(this->type){
            case FilterType::None:{
                int pos = (int) v * this->width + (int) u;
                
                while(pos < 0) pos += this->totalSize;
                while(pos >= this->totalSize) pos -= this->totalSize;
                
                return this->pixels[pos];
            }
                break;
            case FilterType::Bilinear:{
                int px = (int) u;
                int py = (int) v;
                
                const int stride = this->width;
                const SHColor *p0 = this->pixels + px + py * stride;
                
                const SHColor p1 = p0[0 + 0 * stride];
                const SHColor p2 = p0[1 + 0 * stride];
                const SHColor p3 = p0[0 + 1 * stride];
                const SHColor p4 = p0[1 + 1 * stride];
                
                float fx = u - px;
                float fy = v - py;
                float fx1 = 1.0f - fx;
                float fy1 = 1.0f - fy;
                
                int w1 = fx1 * fy1 * 256.0f;
                int w2 = fx * fy1 * 256.0f;
                int w3 = fx1 * fy * 256.0f;
                int w4 = fx * fy * 256.0f;
                
                int outr = p1.r * w1 + p2.r * w2 + p3.r * w3 + p4.r * w4;
                int outg = p1.g * w1 + p2.g * w2 + p3.g * w3 + p4.g * w4;
                int outb = p1.b * w1 + p2.b * w2 + p3.b * w3 + p4.b * w4;
                int outa = p1.a * w1 + p2.a * w2 + p3.a * w3 + p4.a * w4;
                
                return (SHColor){static_cast<unsigned char>(outa >> 8), static_cast<unsigned char>(outr >> 8), static_cast<unsigned char>(outg >> 8), static_cast<unsigned char>(outb >> 8)};
            }
                break;
        }
        
        return (SHColor){0};
    }
    
    SHColor MappingTexture::mixColors(unsigned int su, unsigned int sv,
                               unsigned int eu, unsigned int ev){
        int x = su;
        int y = sv;
        
        int dx = fabs(eu - su), sx = su < eu ? 1 : -1;
        int dy = fabs(ev - sv), sy = sv < ev ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;
        
        SHColor colors;
        
        int count = 0;
        for(;;){
            //            device.setPixel((SHPoint){x, y}, color);
            SHColor stepColor = getPixel(x, y);
            colors.a += stepColor.a;
            colors.r += stepColor.r;
            colors.g += stepColor.g;
            colors.b += stepColor.b;
            
            count++;
            if (x == eu && y == ev) break;
            e2 = err;
            if (e2 > -dx) { err -= dy; x += sx; }
            if (e2 < dy) { err += dx; y += sy; }
        }
        
        colors.a /= count;
        colors.r /= count;
        colors.g /= count;
        colors.b /= count;
        
        return colors;
    }
    
    SHColor MappingTexture::mixARGB(SHColor a, SHColor b, float mixedValue){
        unsigned char alpha = a.a;
        unsigned char red = a.r;
        unsigned char green = a.g;
        unsigned char blue = a.b;
        
        char da = b.a - a.a;
        char dr = b.r - a.r;
        char dg = b.g - a.g;
        char db = b.b - a.b;
        
        alpha += (float) da * mixedValue;
        red += (float) dr * mixedValue;
        green += (float) dg * mixedValue;
        blue += (float) db * mixedValue;
        
        return SHColorMake(alpha << 24 | red << 16 | green << 8 | blue);
    }
    
    SHColor MappingTexture::mixRGB(SHColor a, SHColor b, float mixedValue){
        unsigned char red = a.r;
        unsigned char green = a.g;
        unsigned char blue = a.b;
        
        char dr = b.r - a.r;
        char dg = b.g - a.g;
        char db = b.b - a.b;
        
        red += (float) dr * mixedValue;
        green += (float) dg * mixedValue;
        blue += (float) db * mixedValue;
        
        return SHColorMake(0xFF000000 | red << 16 | green << 8 | blue);
    }
}
