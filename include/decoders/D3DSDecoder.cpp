//
//  3DSDecoder.cpp
//  Aiks_lib
//
//  Created by 7heaven on 16/7/10.
//  Copyright © 2016年 Saint Hsu. All rights reserved.
//

#include "D3DSDecoder.h"
#include <stdlib.h>

#define          HEAD3DS 0x4D4D //header of 3ds file
#define            ED3DS 0x3D3D //main editor block
#define           ED_MTR 0xAFFF //editor material
#define          MAT_N01 0xA000 //editor
#define          ED_CFG1 0x0100
#define          ED_CFG2 0x3D3E
#define           ED_VP1 0x7012
#define           ED_VP2 0x7011
#define           ED_VP3 0x7020
#define           VP_TOP 0x0001
#define        VP_BOTTOM 0x0002
#define          VP_LEFT 0x0003
#define         VP_RIGHT 0x0004
#define         VP_FRONT 0x0005
#define          VP_BACK 0x0006
#define          VP_USER 0x0007
#define           VP_CAM 0xFFFF
#define           VP_LIT 0x0009
#define      VP_DISABLED 0x0010
#define         VP_BOGUS 0x0011
#define           ED_OBJ 0x4000 //object block
#define      OBJ_TRIMESH 0x4100
#define      TRI_VERTEXL 0x4110
#define    TRI_VERTEXOPT 0x4111
#define TRI_MAPPINGCOORS 0x4140
#define   TRI_MAPPINGSTD 0x4170
#define        TRI_FACEL 0x4120
#define       TRI_SMOOTH 0x4150
#define          TRI_MTR 0x4130  //triangle material
#define        TRI_LOCAL 0x4160
#define      TRI_VISIBLE 0x4165
#define          OBJ_LIT 0x4600
#define          LIT_OFF 0x4620
#define         LIT_SPOT 0x4610
#define       LIT_UNKN01 0x465A
#define          OBJ_CAM 0x4700
#define       CAM_UNKN01 0x4710
#define       CAM_UNKN02 0x4720

#define COL_RGB 0x0010
#define COL_TRU 0x0011
#define COL_UNK 0x0013

#define ED_UNKN01 0x1100
#define ED_UNKN02 0x1201
#define ED_UNKN03 0x1300
#define ED_UNKN04 0x1400
#define ED_UNKN05 0x1420
#define ED_UNKN06 0x1450
#define ED_UNKN07 0x1500
#define ED_UNKN08 0x2200
#define ED_UNKN09 0x2201
#define ED_UNKN10 0x2210
#define ED_UNKN11 0x2300
#define ED_UNKN12 0x2302
#define ED_UNKN13 0x2000
#define ED_UNKN14 0xAFFF


namespace sh{
    D3DSDecoder::D3DSDecoder(){
        
    }
    
    D3DSDecoder::~D3DSDecoder(){
        
    }
    
    Object3D * D3DSDecoder::decode(const char * path){
        this->fp = fopen(path, "r");
        printf("path:%s\n", path);
        if(this->fp != NULL){
            
            struct Object3D *object = (Object3D *)malloc(sizeof(struct Object3D));
            
            struct Mesh3D *meshes;
            uint32_t meshesCount = -1;
            
            uint16_t chunk;
            uint32_t length;
            
            size_t chunkRead = readU16(chunk);
            size_t lengthRead = readU32(length);
            
            const size_t fileSize = length;
            
            while(this->fp->_offset < fileSize){
                printf("chunk:0x%X, length:%d\n", chunk, length);
                
                switch(chunk){
                    case HEAD3DS:
                        printf(">>>>>header<<<<<\n");
                        break;
                    case ED3DS:
                        printf(">>>>>edit<<<<<\n");
                        break;
                    case ED_OBJ:
                    {
                        printf(">>>>>object<<<<<\n");
                        
                        uint32_t intrinsicLength = ftell(this->fp) + length - 6;
                        
                        uint8_t size;
                        do{
                            readU8(size);
                        }while(size != 0);
                    }
                        break;
                    case ED_MTR:
                    {
                        unsigned char name[length - 6];
                        int c = 0;
                        unsigned char buffer;
                        
                        printf("name:");
                        do{
                            readU8(buffer);
                            name[c++] = buffer;
                            printf("%c", buffer);
                        }while(c < length - 6);
                        
                        printf("\n");
                    }
                        break;
                    default:
                        fseek(this->fp, length - 6, SEEK_CUR);
                        break;
                }
                
                
                chunkRead = readU16(chunk);
                lengthRead = readU32(length);
            }
            
            fclose(this->fp);
        }
        
        return NULL;
    }
}