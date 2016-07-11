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

namespace sh{
    
    class D3DSDecoder : public AbsDecoder<Object3D *>{
    public:
        D3DSDecoder();
        ~D3DSDecoder();
        
        Object3D * decode(const char * path);
        
    };
}

#endif /* D3DSDecoder_hpp */
