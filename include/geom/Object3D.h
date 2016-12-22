//
//  Object3D.h
//
//  Created by 7heaven on 16/7/10.
//  Copyright © 2016年 Aiks Group. All rights reserved.
//

#ifndef Object3D_h
#define Object3D_h

#include <stdio.h>
#include "math/BasicGeometry.h"

typedef struct Edge3D{
    SHVector3D _vertex0;
    SHVector3D _vertex1;
}Edge3D;

typedef struct Mesh3D{
    SHVector3D *_vertexes; //all vertexes in this mesh
    SHSimpleTri *_triangles; //all triangles in mesh, refer to the index of the _vertexes array
    SHUVCoorF *_uvmaps; //uvmap array
    
    float *_vertexesNormal_m;// modulo of each vertex's normal vector based on the triangles it's in
    
    SHVector3D *_vertexesNormal; //vertex's normal vector
    SHVector3D *_trianglesNormal; //triangle's normal vector
    
    uint64_t _vertexSize;
    uint64_t _trianglesSize;
}Mesh3D;

typedef struct Object3D{
    uint64_t _mesh_count;
    Mesh3D *_meshes;
}Object3D;

#endif /* Object3D_h */
