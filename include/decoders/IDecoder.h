//
//  IDecoder.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/11.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef IDecoder_h
#define IDecoder_h

#include <string.h>
#include <stdint.h>
#include <stdio.h>

namespace sh{
    
template<typename T>
class IDecoder{
public:
    virtual T decode(const char * path) = 0;
    
protected:
    virtual size_t readU8(uint8_t &buffer) = 0;
    virtual size_t readU16(uint16_t &buffer) = 0;
    virtual size_t readU32(uint32_t &buffer) = 0;
    virtual size_t readU64(uint64_t &buffer) = 0;
    
    FILE *fp;
};
}

#endif
