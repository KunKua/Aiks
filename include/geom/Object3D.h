//
//  Object3D.h
//  Aiks_lib
//
//  Created by 7heaven on 16/7/10.
//  Copyright © 2016年 Saint Hsu. All rights reserved.
//

#ifndef Object3D_h
#define Object3D_h

#include <stdio.h>
#include "math/BasicGeometry.h"

typedef struct Edge3D{
    SHVector3D _vertex0;
    SHVector3D _vertex1;
};

typedef struct Mesh3D{
    SHVector3D *_vertexes;
    SHSimpleTri *_triangles;
    SHUVCoorF *_uvmaps;
    
    float *_vertexesNormal_m;
    
    SHVector3D *_vertexesNormal;
    SHVector3D *_trianglesNormal;
    
    uint64_t _vertexSize;
    uint64_t _trianglesSize;
};

typedef struct Object3D{
    uint64_t _mesh_count;
    Mesh3D *_meshes;
}Object3D;

#endif /* Object3D_h */
