//
//  D3DSDecoder.hpp
//  Aiks_lib
//
//  Created by 7heaven on 16/7/10.
//  Copyright © 2016年 Saint Hsu. All rights reserved.
//

#ifndef D3DSDecoder_hpp
#define D3DSDecoder_hpp

#include "AbsDecoder.h"
#include <stdio.h>
#include "geom/Object3D.h"

typedef struct Chunk{
    //chunk head in 2 bytes
    uint16_t _chunk_head;
    
    //chunk length in 4 bytes, include chunk head and length itself
    uint32_t _chunk_length;
    
    //content length
    uint32_t _content_length;
    
    //for convenience
    size_t _checksum_head;
    size_t _checksum_length;
    
    //for convenience, point to end of this chunk
    uint32_t _ins_length;
}Chunk;


namespace sh{
    
    class D3DSDecoder : public AbsDecoder<Object3D *>{
    public:
        D3DSDecoder();
        ~D3DSDecoder();
        
        Object3D * decode(const char * path);
    private:
        Chunk * readChunk();
        
        void decodeMesh(Mesh3D &mesh, Chunk *meshChunk);
        void decodeMaterial();
    };
}

#endif /* D3DSDecoder_hpp */
