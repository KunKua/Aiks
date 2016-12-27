/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef IDevice_h
#define IDevice_h

#include "math/BasicGeometry.h"

namespace aiks {

    class IDevice
	{
    public:
        virtual void update() = 0;
        
        virtual void setPixel(SHPoint position, SHColor color) = 0;
        virtual void setPixels(SHPoint position[], SHColor color) = 0;
        
        virtual void flush(SHRect dirtyRect, SHColor color) = 0;
        virtual void flush(SHColor color) = 0;
        
        virtual double getZDepth(SHPoint pos) = 0;
        virtual void setZDepth(SHPoint pos, double zDepth) = 0;
        
        virtual SHRect getBounds() = 0;
    };
}

#endif /* IDevice_h */
