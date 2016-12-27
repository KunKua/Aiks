/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#ifndef AK_DECODE_ABSDECODER_H
#define AK_DECODE_ABSDECODER_H

#include <stdio.h>

#include "AkTypes.h"

namespace aiks{

template<typename T>
class AbsDecoder 
{
public:
    AbsDecoder(){
        
    }
    ~AbsDecoder(){
        
    }
    
    virtual T decode(const char * path){
        return (T){};
    }
    
protected:
    
    size_t readU8(u8 &buffer){
        size_t result = fread(&buffer, sizeof(uint8_t), 1, fp);
        
        return result == 1 ? result : EOF;
    }
    
    size_t readU16(uint16_t &buffer){
        size_t result = fread(&buffer, sizeof(uint16_t), 1, fp);
        
        return result == 1 ? result : EOF;
    }
    
    size_t readU32(uint32_t &buffer){
        size_t result = fread(&buffer, sizeof(uint32_t), 1, fp);
        
        return result == 1 ? result : EOF;
    }
    
    size_t readU64(uint64_t &buffer){
        size_t result = fread(&buffer, sizeof(uint64_t), 1, fp);
        
        return result == 1 ? result : EOF;
    }
    
    FILE *_fp;
};

}

#endif /* AkAbsDecoder_h */
