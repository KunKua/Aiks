/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef AK_DECODE_3DSDECODER_H
#define AK_DECODE_3DSDECODER_H

#include <stdio.h>

#include "decoders/AkAbsDecoder.h"
#include "geom/AkObject3D.h"

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


namespace aiks {
    
class D3DSDecoder : public AbsDecoder<Object3D>
{
    public:
        D3DSDecoder();
        ~D3DSDecoder();
        
        Object3D decode(const char * path);
    private:
        Chunk readChunk();
        
        void decodeMesh(Mesh3D &mesh, Chunk meshChunk);
        void decodeMaterial();
    };
}

#endif /* Ak3DSDecoder_h */
