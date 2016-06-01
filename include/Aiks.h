/*************************************
 * Copyright 2016 Aiks Group
 * ***********************************/

#ifndef AIKS_AIKS_H
#define AIKS_AIKS_H

//Aiks Header

//SHVersion Header
#include "draw/BasicDraw.h"
#include "draw/Texture.h"
#include "light/FakeLight.h"
#include "light/SimpleDiffuseLight.h"
#include "math/Matrix44.h"
#include "math/Transform.h"
#include "math/Vertex3D.h"

#ifdef TARGET_MAC
#include "device/osx/MacDevice.h"
#include "device/osx/SHHardwareCanvas.h"
#include "device/osx/SHSoftwareCanvas.h"
#endif

#endif