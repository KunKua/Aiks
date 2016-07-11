//
//  AbsDecoder.hpp
//  Aiks_lib
//
//  Created by 7heaven on 16/7/10.
//  Copyright © 2016年 Saint Hsu. All rights reserved.
//

#ifndef AbsDecoder_hpp
#define AbsDecoder_hpp

#include "IDecoder.h"
#include <stdio.h>

namespace sh{

template<typename T>
class AbsDecoder : public IDecoder<T>{
public:
    AbsDecoder(){
        
    }
    ~AbsDecoder(){
        
    }
    
//    virtual T decode(const char *path);
    virtual T decode(const char * path){
        return NULL;
    }
    
protected:
    
    size_t readU8(uint8_t &buffer){
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
    
    FILE *fp;
};
}

#endif /* AbsDecoder_hpp */
