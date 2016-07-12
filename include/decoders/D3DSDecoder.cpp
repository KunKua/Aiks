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

#define           ED_MAT 0xAFFF //editor material

//>>>>>subchunk of editor_material refered to 0xAFFF<<<<<
#define          MAT_N01 0xA000 //material name
#define         COL_AMBI 0xA010 //ambient color [RGB1 & RGB2]
#define          COL_DFS 0xA020 //diffuse color [idem]
#define         COL_SPEC 0xA030 //specular color [idem]
#define        SHININESS 0xA040 //shininess [amount of]
#define       SHIN_STREN 0xA041 //shininess strength
#define           TRANSP 0xA050 //transparency
#define    TRANS_FALLOFF 0xA052 //trans. falloff
#define     REFLECT_BLUR 0xA053 //reflect blur
#define         MAT_TYPE 0xA100 //material type [1=flat 2=gour. 2=phong 4=metal]
#define       SELF_ILLUM 0xA084 //self illum [amount of]
#define         MAT_UNKN 0xA087 // * unknown chunk
#define          TEXTURE 0xA200 // * texture
#define     SPEC_TEXTURE 0xA204 // * specular texture
#define     OPAC_TEXTURE 0xA210 // * opacity texture
#define  S_TRANS_FALLOFF 0xA240 // * some trans. falloff amount (not 0)
#define   S_REFLECT_BLUR 0xA250 // * some reflect. blur
#define        TWO_SIDED 0xA081 // * two sided
#define        TRANS_ADD 0xA083 // * transparency ADD
#define          WIRE_ON 0xA085 // * wire one
#define         FACE_MAP 0xA088 // * face map
#define TRANS_FALLOFF_IN 0xA08A // * trans. falloff IN
#define           SOFTEN 0xA08C // * soften
#define     U_WIRE_THICK 0xA08E // * 3d wire thickness in units (default is in pix)
#define       WIRE_THICK 0xA087 //wire thickness (aways present, in case of forced wire rendering)
// * means optional

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
#define          TRI_MAT 0x4130 //triangle material
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
        this->fp = fopen(path, "rb");
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
                
                switch(chunk){
                    case HEAD3DS:
                        printf("\n>>>>>header<<<<<\n");
                        printf("\n");
                        break;
                    case ED3DS:
                        printf("\n>>>>>edit<<<<<\n");
                        printf("\n");

                        break;
                    case ED_OBJ:
                    {
                        printf("\n>>>>>object<<<<<\n");
                        
                        uint32_t intrinsicLength = ftell(this->fp) + length - 6;
                        
                        uint8_t size;
                        do{
                            readU8(size);
                        }while(size != 0);
                        
                        uint16_t subchunk;
                        uint32_t sublength;
                        
                        readU16(subchunk);
                        
                        while(ftell(this->fp) <= intrinsicLength - 6){
                            switch(subchunk){
                                case OBJ_TRIMESH:{
                                    readU32(sublength);
                                    printf(">>>>>trimesh<<<<<\n");
                                }
                                    break;
                                case TRI_VERTEXL:
                                {
                                    
                                    uint32_t x, y, z;
                                    uint16_t rlength;
                                    readU16(rlength);
                                    int count = 0;
                                    while(rlength-- > 0){
                                        readU32(x), readU32(y), readU32(z);
                                        
                                        //TODO record vertex coor to current mesh
                                        printf(">>>%d:ver->x:%f, y:%f, z:%f\n", count++, *((float*)&x), *((float*)&y), *((float*)&z));
                                    }
                                }
                                    break;
                                case TRI_FACEL:
                                {
                                    uint16_t a, b, c, info;
                                    uint16_t rlength;
                                    readU16(rlength);
                                    int count = 0;
                                    while(rlength-- > 0){
                                        readU16(a), readU16(b), readU16(c), readU16(info);
                                        
                                        printf(">>>>%d:face->a:%d, b:%d, c:%d, info:%d\n", count++, a, b, c, info);
                                    }
                                }
                                    break;
                                case TRI_MAPPINGCOORS:
                                {
                                    uint32_t u, v;
                                    uint16_t rlength;
                                    readU16(rlength);
                                    int count = 0;
                                    while(rlength-- > 0){
                                        readU32(u), readU32(v);
                                        
                                        printf(">>>>%d:uvmap->u:%f, v:%f\n", count++, *((float*)&u), *((float*)&v));
                                    }
                                }
                                    break;
                                default:
                                    printf("sub:%04X of chunk:%04X, length:%d\n", subchunk, chunk, sublength);
                                    fseek(this->fp, sublength - 6, SEEK_CUR);
                                    break;
                            }
                            
                            readU16(subchunk);
                            readU32(sublength);
                        }
                        
                        fseek(this->fp, intrinsicLength, SEEK_SET);
                        printf("\n");

                    }
                        break;
                    case ED_MAT:
                    {
                        printf("\n>>>>>material<<<<<\n");
                        uint16_t subchunk;
                        uint32_t sublength;
                        
                        const uint32_t ins_length = ftell(this->fp) + length - 6;
                        
                        readU16(subchunk);
                        readU32(sublength);
//
                        while(ftell(this->fp) <= ins_length - 6){
                            switch(subchunk){
                                case MAT_N01:
                                {
                                    unsigned char name[sublength];
                                    unsigned char buffer;
                                    int c = 0;
                                    printf("name:");
                                    
                                    do{
                                        readU8(buffer);
                                        printf("%c", buffer);
                                    }while(buffer != '\0');
                                    
                                    printf("\n");
                                }
                                    break;
                                case COL_AMBI:
                                case COL_DFS:
                                case COL_SPEC:
                                {
                                    const char * name = subchunk == COL_AMBI ? "ambient" : (subchunk == COL_DFS ? "diffuse" : "specular");
                                    
                                    uint32_t rLength = sublength - 6;
                                    printf(">>>%s:\n", name, rLength);
                                    while(rLength > 0){
                                        unsigned char buffer;
                                        readU8(buffer);
                                        rLength--;
                                        printf("0x%04X\n", buffer);
                                    }
                                    
                                    printf("<<<%s_end\n", name);
                                }
                                    break;
                                case OPAC_TEXTURE:
                                {
                                    unsigned char name[sublength];
                                    unsigned char buffer;
                                    int c = 0;
                                    printf("opacity_texture:");
                                    
                                    uint32_t ins_length = ftell(this->fp) + sublength - 6;
                                    
                                    uint16_t sschunk;
                                    uint32_t sslength;
                                    readU16(sschunk);
                                    readU32(sslength);
                                    
                                    switch(sschunk){
                                        case 0xA300:
                                        {
                                            printf("\n map name:");
                                            do{
                                                readU8(buffer);
                                                printf("%c", buffer);
                                            }while(sslength-- > 6);
                                            
                                            printf("\n");
                                        }
                                            break;
                                        default:
                                            fseek(this->fp, sslength - 6, SEEK_CUR);
                                            break;
                                    }
                                    
                                    
                                    printf("\n");
                                    
                                    fseek(this->fp, ins_length, SEEK_SET);
                                }
                                    break;
                                case SPEC_TEXTURE:
                                {
                                    unsigned char name[sublength];
                                    unsigned char buffer;
                                    int c = 0;
                                    printf("spec_texture:");
                                    
                                    uint32_t ins_length = ftell(this->fp) + sublength - 6;
                                    
                                    uint16_t sschunk;
                                    uint32_t sslength;
                                    readU16(sschunk);
                                    readU32(sslength);
                                    
                                    switch(sschunk){
                                        case 0xA300:
                                        {
                                            printf("\n map name:");
                                            do{
                                                readU8(buffer);
                                                printf("%c", buffer);
                                            }while(sslength-- > 6);
                                            
                                            printf("\n");
                                        }
                                            break;
                                        default:
                                            fseek(this->fp, sslength - 6, SEEK_CUR);
                                            break;
                                    }
                                    
                                    
                                    printf("\n");
                                    
                                    fseek(this->fp, ins_length, SEEK_SET);
                                }
                                    break;
                                case TEXTURE:
                                {
                                    unsigned char name[sublength];
                                    unsigned char buffer;
                                    int c = 0;
                                    printf("texture:");
                                    
                                    uint32_t ins_length = ftell(this->fp) + sublength - 6;
                                    
                                    uint16_t sschunk;
                                    uint32_t sslength;
                                    readU16(sschunk);
                                    readU32(sslength);
                                    
                                    switch(sschunk){
                                        case 0xA300:
                                        {
                                            printf("\n map name:");
                                            do{
                                                readU8(buffer);
                                                printf("%c", buffer);
                                            }while(sslength-- > 6);
                                            
                                            printf("\n");
                                        }
                                            break;
                                        default:
                                            fseek(this->fp, sslength - 6, SEEK_CUR);
                                    }
                                    
                                    
                                    printf("\n");
                                    
                                    fseek(this->fp, ins_length, SEEK_SET);
                                }
                                    break;
                                default:
                                    printf("unknown_sub:%04X of chunk:%04X, length:%d\n", subchunk, chunk, sublength);
                                    fseek(this->fp, sublength - 6, SEEK_CUR);
                                    break;
                                    
                            }
                            
                            readU16(subchunk);
                            readU32(sublength);
                        }
                        fseek(this->fp, ins_length, SEEK_SET);
                        
                        printf(">>>>>material_end<<<<<\n\n");
                        
                    }
                        break;
                    default:
                        printf("chunk:0x%04X, length:%d\n", chunk, length);
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