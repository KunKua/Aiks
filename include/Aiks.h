/*************************************
 * Copyright 2016 Aiks Group
 * ***********************************/

#ifndef AIKS_AIKS_H
#define AIKS_AIKS_H

// define supported target platform macro which Aiks uses.

#define AK_PLATFORM_UNKNOWN            0
#define AK_PLATFORM_IOS                1
#define AK_PLATFORM_ANDROID            2

#define AK_PLATFORM_WIN32              3
#define AK_PLATFORM_MARMALADE          4
#define AK_PLATFORM_LINUX              5
#define AK_PLATFORM_BADA               6
#define AK_PLATFORM_BLACKBERRY         7
#define AK_PLATFORM_MAC                8
#define AK_PLATFORM_NACL               9
#define AK_PLATFORM_EMSCRIPTEN        10
#define AK_PLATFORM_TIZEN             11
#define AK_PLATFORM_WINRT             12
#define AK_PLATFORM_WP8               13

#define AK_TARGET_PLATFORM  AK_PLATFORM_UNKNOWN

// mac
#if defined(AK_TARGET_OS_MAC) || defined(__APPLE__)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM         AK_PLATFORM_MAC
#endif

// iphone
#if defined(AK_TARGET_OS_IOS)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM         AK_PLATFORM_IOS
#endif

// android
#if defined(ANDROID)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM         AK_PLATFORM_ANDROID
#endif

// WinRT (Windows Store App)
#if defined(WINRT) && defined(_WINRT)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM			AK_PLATFORM_WINRT
#endif

// WP8 (Windows Phone 8 App)
#if defined(WP8) && defined(_WP8)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM			AK_PLATFORM_WP8
#endif

// win32
#if defined(WIN32) && defined(_WINDOWS)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM         AK_PLATFORM_WIN32
#endif

// linux
#if defined(LINUX) && !defined(__APPLE__)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM         AK_PLATFORM_LINUX
#endif

// marmalade
#if defined(MARMALADE)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM         AK_PLATFORM_MARMALADE
#endif

// bada
#if defined(SHP)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM         AK_PLATFORM_BADA
#endif

// qnx
#if defined(__QNX__)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM     AK_PLATFORM_BLACKBERRY
#endif

// native client
#if defined(__native_client__)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM     AK_PLATFORM_NACL
#endif

// Emscripten
#if defined(EMSCRIPTEN)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM     AK_PLATFORM_EMSCRIPTEN
#endif

// tizen
#if defined(TIZEN)
#undef  AK_TARGET_PLATFORM
#define AK_TARGET_PLATFORM     AK_PLATFORM_TIZEN
#endif

#if ! AK_TARGET_PLATFORM
#error "Cannot recognize the target platform"
#endif

//Aiks Header

//SH Version Header
#include "draw/BasicDraw.h"
#include "draw/Texture.h"
#include "draw/MappingTexture.h"
#include "draw/ColorTexture.h"
#include "light/FakeLight.h"
#include "light/SimpleDiffuseLight.h"
#include "math/Matrix44.h"
#include "math/Transform.h"
#include "math/math.h"
#include "geom/Object3D.h"
#include "geom/Vertex3D.h"
#include "decoders/D3DSDecoder.h"

#if AK_TARGET_PLATFORM == AK_PLATFORM_MAC
#include "device/osx/MacDevice.h"
#include "device/osx/SHHardwareCanvas.h"
#include "device/osx/SHSoftwareCanvas.h"
#endif

#endif