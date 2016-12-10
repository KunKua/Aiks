//
//  SHHardwareCanvas.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "device/osx/SHHardwareCanvas.h"
#import "device/osx/MacDevice.h"
#import "math/BasicGeometry.h"

#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <GLKit/GLKMatrix4.h>

@implementation SHHardwareCanvas{
    MacDevice *_nativePtr;
    
    SHColor _backgroundColor;
    
    double *_zDepth;
    unsigned long _rawDataSize;
    unsigned long _canvasPixelSize;
    
    unsigned char *_rawData;
    
    GLuint _textureId;
}

- (instancetype) initWithBackgroundColor:(SHColor) color{
    if(self = [super init]){
        _backgroundColor = color;
        [self initProcess];

    }
    
    return self;
}

- (instancetype) init{
    if(self = [super init]){
        [self initProcess];

    }
    
    return self;
}

- (void) prepareOpenGL{
    [self initProcess];
}

- (void) initProcess{
    _nativePtr = new MacDevice(self);
    
    GLuint attribs[] =
    {
        NSOpenGLPFANoRecovery,
        NSOpenGLPFAWindow,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFAAccumSize, 0,
        0
    } ;
    
    NSOpenGLPixelFormat* fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes: (NSOpenGLPixelFormatAttribute*) attribs];
    
    [self initRawDataBackend];
    [self initDepthStore];
}

- (void) initRawDataBackend{
    _canvasPixelSize = self.frame.size.width * self.frame.size.height;
    _rawDataSize = _canvasPixelSize * 3;
    
    _rawData = (unsigned char *) malloc(_rawDataSize);
    
    for(int i = 0; i < _canvasPixelSize; i++){
        _rawData[i * 3] = _backgroundColor.r;
        _rawData[i * 3 + 1] = _backgroundColor.g;
        _rawData[i * 3 + 2] = _backgroundColor.b ;
    }
    
    NSOpenGLContext *context = [self openGLContext];
    if(context != nil){
        [context makeCurrentContext];
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        
        glViewport(0, 0, self.frame.size.width, self.frame.size.height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        float ratio = self.frame.size.width / self.frame.size.height;
        glOrtho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);
        
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        
    }
}

- (void) setFrame:(NSRect)frame{
    [super setFrame:frame];
    
    [self initRawDataBackend];
    [self initDepthStore];
}

- (void) initDepthStore{
    _zDepth = (double *) malloc(sizeof(double) * _canvasPixelSize);
    memset(_zDepth, 600, sizeof(double) * _canvasPixelSize);
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    glLoadIdentity();
    // Drawing code here.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, self.frame.size.width, self.frame.size.height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *) _rawData);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
    }
    glEnd();
    glFlush();
}


# pragma mark - override

- (void) update{
    [self display];
    [self setNeedsDisplay:YES];
    [self displayIfNeeded];
    
    memset(_zDepth, 600, sizeof(double) * _canvasPixelSize);
}


- (sh::IDevice *) getNativePtr{
    return _nativePtr;
}

- (double) getZDepth:(SHPoint)pos{
    int position = pos.y * self.frame.size.width + pos.x;
    if(position < 0 || position > _canvasPixelSize) return 0;
    
    
    return _zDepth[position];
    
}

- (void) setZDepth:(double) zDepth position:(SHPoint) pos{
    int position = pos.y * self.frame.size.width + pos.x;
    if(position < 0 || position > _canvasPixelSize) return;
    
    _zDepth[position] = zDepth;
}

- (void) flushWithDirtyRect:(SHRect) dirtyRect color:(SHColor) color{
    if(dirtyRect.x < 0 || dirtyRect.y < 0 || dirtyRect.x + dirtyRect.w > self.frame.size.width || dirtyRect.y + dirtyRect.h > self.frame.size.height) return;
    
    for(int i = dirtyRect.y; i < dirtyRect.y + dirtyRect.h; i++){
        int start = dirtyRect.x + i * self.frame.size.width;
        for(int j = start; j < start + dirtyRect.w; j++){
            _rawData[j * 3] = color.r;
            _rawData[j * 3 + 1] = color.g;
            _rawData[j * 3 + 2] = color.b;
        }
    }
}

- (void) flushWithColor:(SHColor) color{
    for(int i = 0; i < _canvasPixelSize; i++){
        _rawData[i * 3] = color.r;
        _rawData[i * 3 + 1] = color.g;
        _rawData[i * 3 + 2] = color.b;
    }

}

- (void) setPixel:(SHPoint) position color:(SHColor) color{
    
    int positionOffset = (self.bounds.size.width * position.y + position.x) * 3;
    
    if(positionOffset < 0 || positionOffset > _rawDataSize) return;
    
    _rawData[positionOffset] = color.r;
    _rawData[positionOffset + 1] = color.g;
    _rawData[positionOffset + 2] = color.b;
}

- (void) setPixels:(SHPoint [])positions color:(SHColor)color{
    size_t length = sizeof(&positions) / sizeof(positions[0]);
    
    NSLog(@"length:%zu", length);
    
    for(int i = 0; i < length; i++){
        [self setPixel:positions[i] color:color];
    }
}

- (SHRect) getBounds{
    return SHRectMake(0, 0, self.frame.size.width, self.frame.size.height);
}

- (void) dealloc{
    free(_rawData);
    delete _nativePtr;
    free(_zDepth);
}

@end
