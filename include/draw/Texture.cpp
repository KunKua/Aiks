//
//  Texture.cpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/16.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "draw/Texture.h"
#include <math.h>

namespace sh{
    Texture::Texture(SHColor *pixels, unsigned int width, unsigned int height){
        this->pixels = pixels;
        this->width = width;
        this->height = height;
        
        this->totalSize = this->width * this->height;
    }
    
    SHColor Texture::getPixel(unsigned int u, unsigned int v){
        int pos = v * this->width + u;
        
        while(pos < 0) pos += this->totalSize;
        while(pos >= this->totalSize) pos -= this->totalSize;
        
        return this->pixels[pos];
    }
    
    SHColor Texture::getPixelF(float u, float v){
        float ru = u * this->width;
        float rv = v * this->height;
        
        int x = (int) (ru);
        int y = (int) (rv);
        
        ru = ru - x;
        rv = rv - y;
        
        if(ru == 0 && rv == 0){
            return getPixel(x, y);
        }else{
            if(ru == 0){
                SHColor lowerY = getPixel(x, y);
                SHColor upperY = getPixel(x, y + 1);
                
                return mixRGB(lowerY, upperY, rv);
            }else if(rv == 0){
                SHColor lowerX = getPixel(x, y);
                SHColor upperX = getPixel(x + 1, y);
                
                return mixRGB(lowerX, upperX, ru);
            }else{
                SHColor tlC = getPixel(x, y);
                SHColor trC = getPixel(x + 1, y);
                SHColor blC = getPixel(x, y + 1);
                SHColor brC = getPixel(x + 1, y);
                
                SHColor mixLeft = mixRGB(tlC, blC, rv);
                SHColor mixRight = mixRGB(trC, brC, rv);
                
                return mixRGB(mixLeft, mixRight, ru);
            }
        }
    }
    
    SHColor Texture::getPixelFiltered(unsigned int u, unsigned int v,
                                      unsigned int lu, unsigned int lv,
                                      unsigned int tu, unsigned int tv,
                                      unsigned int ru, unsigned int rv,
                                      unsigned int bu, unsigned int bv){
        SHColor left = mixColors(lu, lv, u, v);
        SHColor right = mixColors(u, v, ru, rv);
        SHColor top = mixColors(tu, tv, u, v);
        SHColor bottom = mixColors(u, v, bu, bv);
        
        return mixARGB(mixARGB(left, right, 0.5f), mixARGB(top, bottom, 0.5f), 0.5f);
    }
    
    SHColor Texture::mixColors(unsigned int su, unsigned int sv,
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
    
    SHColor Texture::mixARGB(SHColor a, SHColor b, float mixedValue){
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
    
    SHColor Texture::mixRGB(SHColor a, SHColor b, float mixedValue){
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