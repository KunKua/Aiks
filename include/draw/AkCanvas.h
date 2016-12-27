/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef AK_DRAW_CANVAS_H
#define AK_DRAW_CANVAS_H

#include <stdio.h>
#include "math/BasicGeometry.h"
#include "device/IDevice.h"
#include "geom/Vertex3D.h"
#include "draw/Texture.h"
#include "light/ILight.h"

namespace aiks {

class Canvas2D
{
    public:
		Canvas2D();
		Canvas2D(IDevice &device);
		virtual ~Canvas2D();

		void drawColor(ColorB& color);
		void clear(ColorB& color);

		void drawPoint(Vec2 position,ColorB& color);
        void drawLine(Vec2 start, Vec2 end, ColorB& color);
        void drawTriangle(SHPoint a, SHPoint b, SHPoint c, SHColor color);
        void drawPerspTriangle(Vertex3D *a, Vertex3D *b, Vertex3D *c, Texture &texture, ILight &light);
    private:
        void drawSubTri(IDevice &device, SHPoint a, SHPoint b, SHPoint c, SHColor color);
        void drawSubPerspTri(IDevice &device, Vertex3D *a, Vertex3D *b, Vertex3D *c, Texture &texture, ILight &light);
        static SHPoint getStep(SHPoint p0, SHPoint p1, float s);

		IDevice _device;
}; 
    
}

#endif /* BasicDraw_h */
