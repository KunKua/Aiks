//
//  MacDevice.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/16.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef MacDevice_h
#define MacDevice_h

#include "device/IDevice.h"
#include "math/BasicGeometry.h"
#include "device/osx/IDevice_osx.h"

class MacDevice : public sh::IDevice{
public:
    MacDevice(id<IDevice_osx> device);
    
    void update();
    
    void setPixel(SHPoint position, SHColor color);
    void setPixels(SHPoint position[], SHColor color);
    
    void flush(SHRect dirtyRect, SHColor color);
    void flush(SHColor color);
    
    double getZDepth(SHPoint pos);
    void setZDepth(SHPoint pos, double zDepth);
    SHRect getBounds();
private:
    id<IDevice_osx> _device;
};


#endif