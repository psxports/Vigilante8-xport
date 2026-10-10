#include "psx.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>

void sub_800165CC(uint32);
uint32 sub_80011834(void);
void sub_80019E7C(uint32);
uint32 sub_8001D3D8(void);
uint32 sub_8001D370(void);
uint32 sub_8001A1E8(uint32,uint32,uint32,uint32);
uint32 sub_8001A2AC(uint32,uint32,uint32);
uint32 sub_80043CE0(uint32);
uint32 sub_80019034(uint32,uint32);
uint32 sub_800190A8(uint32);
uint32 sub_8001AC44(uint32,uint32,uint32,uint32);
uint32 sub_80044EFC(uint32,uint32,uint32);
uint32 sub_8001D708(uint32);
uint32 sub_8001DC1C(uint32);
void sub_80019E20(void);
void sub_8001A0AC(uint32,uint32);
uint32 sub_80011A10(void);
void v8_native_1A4F8(uint32,uint32);
uint32 v8_native_1DE08(uint32);
uint32 sub_8001A584(uint32);
uint32 sub_80017160(void);
void sub_800126F0(void);
uint32 sub_8001A4AC(uint32,uint32);
uint32 sub_8004445C(uint32,uint32,uint32);
uint32 sub_8001AF48(uint32,uint32);
uint32 sub_8001A994(uint32);
uint32 sub_800183EC(uint32,uint32);
uint32 v8_native_1D9C0(const MATRIX *,uint32);
uint32 v8_native_1A24C(const PSX_RECT *);
uint32 v8_native_1A2CC(const PSX_RECT *,uint32,uint32,uint32);
void v8_native_19A58(uint32,uint32,const PSX_RECT *,uint32,uint32,uint32);
void v8_native_shell_bitmap_draw(uint32,uint32,uint32,uint32,uint32);

/* The original light setter performs ordered halfword loads and stores */
void v8_native_1D404(uint32 light,uint32 vector,uint32 color)
{
    uint32 twice=light<<1u, destination=0x8006F720u+light*6u;
    uint32 value=r_u16(vector);
    w_u16(destination,(uint16)value);
    value=r_u16(vector+2u); w_u16(destination+2u,(uint16)value);
    value=r_u16(vector+4u); w_u16(destination+4u,(uint16)value);
    destination=0x8006F760u+twice;
    w_u16(destination,(uint16)((color&255u)<<4u));
    w_u16(destination+6u,(uint16)((color>>4u)&0xFF0u));
    w_u16(destination+12u,(uint16)((color>>12u)&0xFF0u));
}

void v8_native_shell_1A30(uint32 base,uint32 count,uint32 text)
{
    uint32 resources=r_u32(base+0x13388u), font, index=0u, odd=1u, length;
    PSX_RECT rectangle;
    font=sub_80019034(resources+r_u32(resources+8u),1u);
    sub_8001A0AC(base+0x3ECu,0x00326478u);
    sub_8001A0AC(base+0x3F4u,0u);
    w_u8(font+4u,64u); w_u8(font+5u,64u); w_u8(font+6u,64u);
    while ((sint32)index<(sint32)count)
    {
        rectangle.x=(sint16)((608u/(count*2u))*odd);
        rectangle.y=442; rectangle.w=0; rectangle.h=0;
        ++index; odd+=2u;
        v8_native_19A58(font,text,&rectangle,10u,index,count*2u);
        length=0u;
        while(r_u8(text+length)!=0u) ++length;
        text+=length+1u;
    }
    (void)sub_800190A8(font);
}

uint32 v8_native_shell_266C(uint32 base)
{
    uint32 resources, header, center, line0, line1, font, object, last=0xFFFFFFFFu;
    uint32 current=0u, minimum=0u, maximum=2u, index, sprite, input, target, result;
    uint32 a,b,c;
    MATRIX matrix;
    PSX_RECT rectangle={90,296,320,124}, cursor={26,0,64,64};
    resources=r_u32(base+0x13388u);
    header=resources+r_u32(resources+8u);
    center=442u-(r_u8(header+6u)>>1u);
    sub_800165CC(0u);
    (void)sub_80011834();
    SetDispMask(0);
    (void)sub_80019E7C(0u);
    /* Preserve the grouped source loads of the original matrix copy */
    a=r_u32(0x800568B4u); b=r_u32(0x800568B8u); c=r_u32(0x800568BCu);
    xport_store_le32((uint8*)&matrix,a); xport_store_le32((uint8*)&matrix+4u,b); xport_store_le32((uint8*)&matrix+8u,c);
    a=r_u32(0x800568C0u); b=r_u32(0x800568C4u); c=r_u32(0x800568C8u);
    xport_store_le32((uint8*)&matrix+12u,a); xport_store_le32((uint8*)&matrix+16u,b); xport_store_le32((uint8*)&matrix+20u,c);
    a=r_u32(0x800568CCu); b=r_u32(0x800568D0u);
    xport_store_le32((uint8*)&matrix+24u,a); xport_store_le32((uint8*)&matrix+28u,b);
    a=r_u32(base+0x618u); b=r_u32(base+0x61Cu); c=r_u32(base+0x620u);
    xport_store_le32((uint8*)&matrix+20u,a); xport_store_le32((uint8*)&matrix+24u,b); xport_store_le32((uint8*)&matrix+28u,c);
    (void)sub_8001D3D8();
    v8_native_1D404(1u,base+0x628u,0xFFFFFFu);
    (void)v8_native_1D9C0(&matrix,512u);
    (void)sub_8001D370();
    resources=r_u32(base+0x13388u);
    v8_native_shell_bitmap_draw(base,resources+r_u32(resources+16u),base+0x108Cu,base+0x108Cu,0u);
    resources=r_u32(base+0x13388u); header=resources+r_u32(resources+8u);
    line0=sub_8001A1E8(0u,center,640u,r_u8(header+6u));
    line1=v8_native_1A24C(&rectangle);
    (void)sub_80043CE0(0u);
    resources=r_u32(base+0x13388u);
    font=sub_80019034(resources+r_u32(resources+4u),1u);
    object=sub_8001AC44(r_u32(base+0x13390u),0u,128u,0u);
    (void)sub_80044EFC(object+72u,0u,12u);
    (void)sub_8001D708(object); (void)sub_8001DC1C(object);
    for (;;)
    {
        sub_80019E20(); (void)VSync(0);
        if(last!=minimum)
        {
            (void)sub_8001A2AC(line0,0u,center); last=minimum;
            if(minimum!=0u) v8_native_shell_1A30(base,(sint8)r_u8(0x80065319u)<0?3u:4u,base+0x630u);
            else v8_native_shell_1A30(base,(sint8)r_u8(0x80065319u)<0?2u:3u,base+0x650u);
            (void)sub_8001A2AC(line1,90u,296u);
        }
        rectangle.y=296; rectangle.h=(sint16)(r_u8(r_u32(font)+7u)+2u);
        for(index=minimum;(sint32)index<=(sint32)maximum;++index)
        {
            if(index==current) {w_u8(font+4u,128u);w_u8(font+5u,128u);w_u8(font+6u,128u);}
            else {w_u8(font+4u,124u);w_u8(font+5u,96u);w_u8(font+6u,0u);}
            v8_native_19A58(font,r_u32(base+0x11DA0u+index*4u),&rectangle,0x4440u,current,minimum);
            rectangle.y=(sint16)((uint16)rectangle.y+(uint16)rectangle.h);
        }
        SetDispMask(1);
        cursor.y=(sint16)(280u+(r_u8(r_u32(font)+7u)+2u)*(current-minimum));
        sprite=v8_native_1A2CC(&cursor,32u,32u,0xFFFFFFFFu);
        for (;;)
        {
            (void)sub_80011A10();
            w_u16(object+66u,(uint16)(r_u16(object+66u)+64u));
            (void)sub_8001D708(object); v8_native_1A4F8(sprite,0u); (void)v8_native_1DE08(object);
            DrawOTag((uint32*)psx_addr(r_u32(0x80065910u)+0x3FFCu,4u));
            (void)VSync(0); (void)DrawSync(0);
            (void)sub_8001A584(sprite); (void)sub_80017160(); sub_800126F0();
            input=r_u32(0x80065930u)|r_u32(0x80065934u);
            if((input&0x00200000u)!=0u&&(sint8)r_u8(0x80065319u)>=0)
            {
                (void)sub_8001A4AC(sprite,(uint32)(sint32)(sint8)r_u8(0x80065319u));
                result=sub_8004445C(1u,r_u32(base+0x1338Cu),8u);
                current=0xFFFFFFFFu; goto cleanup;
            }
            if((input&0x58500000u)!=0u)break;
        }
        v8_native_1A4F8(sprite,0u); result=sub_8001A584(sprite);
        result=(uint32)DrawSync(0); (void)sub_8001A4AC(sprite,result);
        (void)sub_8004445C(1u,r_u32(base+0x1338Cu),(input&0x08400000u)!=0u?8u:0u);
        if((input&0x10000000u)!=0u&&(sint32)minimum<(sint32)current)--current;
        if((input&0x40000000u)!=0u&&(sint32)current<(sint32)maximum)++current;
        if(minimum!=0u&&(input&0x00100000u)!=0u){current=0u;minimum=0u;maximum=2u;}
        if((input&0x08400000u)==0u||current>=7u)continue;
        target=r_u32(base+0x668u+current*4u); result=target;
        if(target==base+0x2B38u){minimum=3u;current=3u;maximum=4u;continue;}
        if(target==base+0x2B48u){minimum=5u;current=5u;maximum=6u;continue;}
        if(target==base+0x2B58u)current=4u;
        else if(target==base+0x2B60u)current=0u;
        else if(target==base+0x2B68u)current=1u;
        else if(target==base+0x2B70u)current=2u;
        else if(target==base+0x2B78u)current=3u;
        else {fprintf(stderr,"Untranslated Shell266C modified dispatch target %08X\n",target);abort();}
        break;
    }
cleanup:
    (void)sub_8001AF48(object,result);
    (void)sub_8001A994(r_u32(base+0x13390u));
    result=sub_800190A8(font);
    (void)sub_800183EC(line1,result);
    return current;
}
