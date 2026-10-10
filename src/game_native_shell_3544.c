#include "psx.h"
#include <stdio.h>
#include <stdlib.h>

uint32 sub_80011834(void);
uint32 sub_80015F80(uint32);
uint32 sub_8001A8FC(uint32);
void sub_800165CC(uint32);
void sub_80019E7C(uint32);
void sub_80019E20(void);
void sub_80045088(uint32);
uint32 sub_80019034(uint32,uint32);
uint32 sub_800190A8(uint32);
void v8_native_19A58(uint32,uint32,const PSX_RECT *,uint32,uint32,uint32);
void v8_native_shell_1A30(uint32,uint32,uint32);
void v8_native_shell_223C(uint32);
void v8_native_shell_DC18(uint32,uint32,uint32,uint32,uint32);
uint32 v8_native_1A2CC(const PSX_RECT *,uint32,uint32,uint32);
uint32 v8_native_1A24C(const PSX_RECT *);
uint32 sub_8001A2AC(uint32,uint32,uint32);
void sub_8001A0AC(uint32,uint32);
MATRIX *v8_native_16DA8(MATRIX *);
uint32 sub_8001D3D8(void);
void v8_native_1D404(uint32,uint32,uint32);
uint32 v8_native_1D9C0(const MATRIX *,uint32);
uint32 sub_8001AC44(uint32,uint32,uint32,uint32);
uint32 sub_8001D708(uint32);
uint32 sub_8001DC1C(uint32);
uint32 sub_80011A10(void);
uint32 sub_8001D370(void);
void v8_native_1A4F8(uint32,uint32);
uint32 v8_native_1DE08(uint32);
void v8_native_1DCC8(uint32,const MATRIX *);
uint32 sub_8001A584(uint32);
uint32 sub_800119C0(uint32);
uint32 sub_800120D4(void);
void v8_native_4454C(uint32,uint32,uint32);
uint32 sub_8004445C(uint32,uint32,uint32);
uint32 sub_8001A4AC(uint32,uint32);
uint32 sub_800183EC(uint32,uint32);
uint32 sub_8001AF48(uint32,uint32);
void sub_8001AA38(uint32);

static uint32 shell3544_table(uint32 character)
{
    return r_u32(0x8006590Cu) + (character << 3u);
}

static uint32 shell3544_level(uint32 base,uint32 character,uint32 stage)
{
    uint32 row=r_u32(shell3544_table(character)+8u)+(stage<<4u);
    return base+0x11BA0u+r_u8(row)*20u;
}

static void shell3544_text(uint32 font,uint32 text,uint32 rectangle,uint32 flags)
{
    v8_native_19A58(font,text,(const PSX_RECT *)psx_addr(rectangle,8u),flags,0u,0u);
}

static uint32 shell3544_normalize_pair(const sint16 *input, sint16 *output)
{
    sint32 first = (sint32)(sint16)xport_load_le16((const uint8 *)input);
    sint32 second = (sint32)(sint16)xport_load_le16((const uint8 *)input + 2u);
    uint32 root = SquareRoot0((sint32)((uint32)(first * first) + (uint32)(second * second)));
    sint32 numerator;
    uint32 quotient;

    first = (sint32)(sint16)xport_load_le16((const uint8 *)input);
    numerator = (sint32)((uint32)first << 12u);
    quotient = root == 0u ? (numerator < 0 ? 1u : 0xFFFFFFFFu) : (uint32)((sint64)numerator / (sint32)root);
    xport_store_le16((uint8 *)output, (uint16)quotient);
    second = (sint32)(sint16)xport_load_le16((const uint8 *)input + 2u);
    numerator = (sint32)((uint32)second << 12u);
    quotient = root == 0u ? (numerator < 0 ? 1u : 0xFFFFFFFFu) : (uint32)((sint64)numerator / (sint32)root);
    xport_store_le16((uint8 *)output + 2u, (uint16)quotient);
    return root;
}

uint32 v8_shell_3544(uint32 base,uint32 character)
{
    uint32 stage=0u,state=0u,flags,count,value,asset,model_asset,font,heading;
    uint32 saved_rectangle,name_font,description_font,objects[8],cursor,marker;
    uint32 index,level,previous_level,raw=0u,input,bit,result=0u,slot,source,record;
    sint32 movement;
    MATRIX matrix;
    PSX_RECT rectangle;
    uint32 polygon[6];
    sint16 pair[2];
    uint16 first_x,first_y,last_x,last_y;
    sint32 offset_x,offset_y;

    flags=r_u8(0x80065950u+character);
    if(flags==0u)w_u8(0x80065950u+character,1u);
    count=r_u32(shell3544_table(character)+4u);
    flags=r_u8(0x80065950u+character);
    if((sint32)flags<(sint32)(1u<<(count&31u)))
        stage=31u-(uint32)Lzc((sint32)flags);
    else
        while((sint32)stage<(sint32)(count-1u) && ((flags>>(stage&31u))&1u)!=0u)
            ++stage;
    (void)sub_80011834();
    model_asset=sub_8001A8FC(sub_80015F80(base+0x684u));
    asset=sub_80015F80(base+0x698u);
    sub_800165CC(0u);SetDispMask(0);sub_80019E7C(0u);
    v8_native_shell_223C(base);sub_80019E20();
    v8_native_shell_DC18(base,asset,0u,0u,0u);sub_80045088(asset);
    asset=r_u32(base+0x13388u);
    font=sub_80019034(asset+r_u32(asset+4u),1u);
    w_u8(font+4u,124u);w_u8(font+5u,96u);w_u8(font+6u,0u);
    shell3544_text(font,base+0x6F4u,base+0x11DFCu,0x444Au);
    (void)sub_800190A8(font);
    v8_native_shell_1A30(base,4u,base+0x700u);
    rectangle=*(PSX_RECT *)psx_addr(base+0x11DF4u,8u);
    heading=v8_native_1A2CC(&rectangle,(uint32)((sint32)rectangle.w/2),(uint32)((sint32)rectangle.h/2),0u);
    saved_rectangle=v8_native_1A24C((const PSX_RECT *)psx_addr(base+0x11DE4u,8u));
    asset=r_u32(base+0x13388u);
    name_font=sub_80019034(asset+r_u32(asset+8u),0u);
    asset=r_u32(base+0x13388u);
    description_font=sub_80019034(asset+r_u32(asset+12u),0u);
    for(index=0u;(sint32)index<(sint32)r_u32(r_u32(model_asset)+16u);++index)
    {
        value=r_u32(r_u32(r_u32(model_asset)+20u)+index*4u);
        w_u32(value+4u,r_u32(value+4u)|16u);
    }
    (void)v8_native_16DA8(&matrix);
    xport_store_le32((uint8 *)&matrix+20u,r_u32(base+0x6D0u));
    xport_store_le32((uint8 *)&matrix+24u,r_u32(base+0x6D4u));
    xport_store_le32((uint8 *)&matrix+28u,r_u32(base+0x6D8u));
    (void)sub_8001D3D8();v8_native_1D404(1u,base+0x724u,0xFFFFFFu);
    (void)v8_native_1D9C0(&matrix,512u);
    ((uint8 *)polygon)[3]=5u;
    ((uint8 *)polygon)[7]=40u;
    for(index=0u;(sint32)index<(sint32)r_u32(shell3544_table(character)+4u);++index)
    {
        level=shell3544_level(base,character,index);
        objects[index]=sub_8001AC44(model_asset,r_u16(level),128u,0u);
        count=r_u32(shell3544_table(character)+4u);
        w_u32(objects[index]+72u,0u);
        w_u32(objects[index]+76u,((index*2u-count+1u)*3u)<<11u);
        w_u32(objects[index]+80u,0xFFFF8000u);
        (void)sub_8001D708(objects[index]);
        if(index!=0u)
        {
            previous_level=shell3544_level(base,character,index-1u);
            first_x=(uint16)r_u16(previous_level+12u);
            previous_level=shell3544_level(base,character,index-1u);
            first_y=(uint16)r_u16(previous_level+14u);
            level=shell3544_level(base,character,index);
            last_x=(uint16)r_u16(level+12u);
            level=shell3544_level(base,character,index);
            last_y=(uint16)r_u16(level+14u);
            pair[0]=(sint16)(uint16)(last_x-first_x);
            pair[1]=(sint16)(uint16)(last_y-first_y);
            (void)shell3544_normalize_pair(pair, pair);
            offset_x=(sint32)pair[1]/1024;
            offset_y=(sint32)pair[0]/1024;
            xport_store_le16((uint8 *)polygon+8u,(uint16)(first_x+offset_x));
            xport_store_le16((uint8 *)polygon+10u,(uint16)(first_y-offset_y));
            xport_store_le16((uint8 *)polygon+12u,(uint16)(first_x-offset_x));
            xport_store_le16((uint8 *)polygon+14u,(uint16)(first_y+offset_y));
            xport_store_le16((uint8 *)polygon+16u,(uint16)(last_x+offset_x));
            xport_store_le16((uint8 *)polygon+18u,(uint16)(last_y-offset_y));
            xport_store_le16((uint8 *)polygon+20u,(uint16)(last_x-offset_x));
            xport_store_le16((uint8 *)polygon+22u,(uint16)(last_y+offset_y));
            flags=r_u8(0x80065950u+character);
            xport_store_le16((uint8 *)polygon+4u,(uint16)((sint32)flags<(sint32)(1u<<(index&31u))?255u:0xFF00u));
            ((uint8 *)polygon)[6]=0u;
            DrawPrim(polygon);
        }
    }
    cursor=sub_8001AC44(model_asset,10u,128u,0u);
    count=r_u32(shell3544_table(character)+4u);
    w_u32(cursor+72u,0u);w_u32(cursor+76u,((stage*2u-count+1u)*3u)<<11u);
    w_u32(cursor+80u,0xFFFF8000u);(void)sub_8001DC1C(cursor);
    marker=sub_8001AC44(model_asset,11u,128u,0u);
    w_u32(marker+72u,0u);w_u32(marker+76u,0u);w_u32(marker+80u,0u);
    (void)sub_8001D708(marker);(void)sub_8001DC1C(marker);
frame:
    (void)sub_80011A10();
    if(state==0u)
    {
        level=shell3544_level(base,character,stage);
        rectangle.x=(sint16)(uint16)(r_u16(level+12u)-16u);
        level=shell3544_level(base,character,stage);
        rectangle.y=(sint16)(uint16)(r_u16(level+14u)-16u);
        rectangle.w=32;rectangle.h=32;
        flags=r_u8(0x80065950u+character)>>(stage&31u);
        raw=v8_native_1A2CC(&rectangle,16u,16u,0xFFFFFFFFu);
        sub_80019E20();
        (void)sub_8001A2AC(saved_rectangle,(uint32)(sint32)(sint16)r_u16(base+0x11DE4u),(uint32)(sint32)(sint16)r_u16(base+0x11DE6u));
        level=shell3544_level(base,character,stage);
        shell3544_text(name_font,r_u32(level+4u),base+0x11DE4u,2u);
        level=shell3544_level(base,character,stage);
        shell3544_text(description_font,r_u32(level+8u),base+0x11DE4u,6u);
        sub_8001A0AC(base+0x11DECu,0u);
        value=flags==0u?base+0x11B94u:(flags==1u?base+0x754u:((flags&1u)!=0u?base+0x72Cu:base+0x740u));
        shell3544_text(name_font,value,base+0x11DECu,2u);
        ++state;w_u16(marker+66u,0u);
    }
    if(state==1u)
    {
        count=r_u32(shell3544_table(character)+4u);
        value=(((stage*2u-count+1u)*3u)<<11u)-r_u32(cursor+76u);
        movement=(sint32)value/16;
        w_u32(cursor+76u,r_u32(cursor+76u)+(uint32)movement);
        if(movement==0)++state;
        (void)sub_8001D708(cursor);(void)sub_8001D370();
        v8_native_1A4F8(heading,0u);(void)v8_native_1DE08(cursor);
        for(index=0u;(sint32)index<(sint32)r_u32(shell3544_table(character)+4u);++index)
        {
            flags=r_u8(0x80065950u+character);
            value=(sint32)flags<(sint32)(1u<<(index&31u))?0u:128u;
            SetBackColor((sint32)value,(sint32)value,(sint32)value);
            v8_native_1DCC8(objects[index],(const MATRIX *)psx_addr(0x8006F680u,sizeof(MATRIX)));
        }
        DrawOTag((uint32 *)psx_addr(r_u32(0x80065910u)+0x3FFCu,4u));
        DrawSync(0);result=sub_8001A584(heading);
        result=sub_800119C0(r_u32(0x80065308u));
    }
    if(state==2u)
    {
        w_u16(marker+66u,(uint16)(r_u16(marker+66u)+64u));
        (void)sub_8001D708(marker);v8_native_1A4F8(raw,0u);(void)v8_native_1DE08(marker);
        DrawOTag((uint32 *)psx_addr(r_u32(0x80065910u)+0x3FFCu,4u));
        DrawSync(0);VSync(0);result=sub_8001A584(raw);
    }
    (void)sub_800120D4();SetDispMask(1);
    input=r_u32(0x80065930u);
    if((input&0x58D00000u)!=0u)
    {
        v8_native_4454C(1u,r_u32(base+0x1338Cu),(input&0x50000000u)!=0u?9u:0u);
        v8_native_1A4F8(raw,0u);result=sub_8001A584(raw);state=0u;
        (void)sub_8001A4AC(raw,result);
        input=r_u32(0x80065930u);
        if((input&0x40000000u)!=0u && (sint32)stage<(sint32)(r_u32(shell3544_table(character)+4u)-1u))++stage;
        if((r_u32(0x80065930u)&0x10000000u)!=0u && stage!=0u)--stage;
    }
    SetDispMask(1);
    if((r_u32(0x80065930u)&0x08400000u)!=0u)
    {
        flags=r_u8(0x80065950u+character);bit=1u<<(stage&31u);
        if((sint32)flags<(sint32)bit)(void)sub_8004445C(1u,r_u32(base+0x1338Cu),11u);
        if((r_u32(0x80065930u)&0x08400000u)!=0u && (sint32)r_u8(0x80065950u+character)>=(sint32)bit)goto cleanup;
    }
    if((r_u32(0x80065930u)&0x00900000u)==0u)goto frame;
cleanup:
    (void)sub_8004445C(1u,r_u32(base+0x1338Cu),(r_u32(0x80065930u)&0x08400000u)!=0u?7u:0u);
    result=sub_800183EC(saved_rectangle,result);
    result=sub_8001A4AC(heading,result);
    for(index=0u;(sint32)index<(sint32)r_u32(shell3544_table(character)+4u);++index)
        result=sub_8001AF48(objects[index],result);
    result=sub_8001AF48(cursor,result);result=sub_8001AF48(marker,result);
    sub_8001AA38(model_asset);(void)sub_800190A8(name_font);(void)sub_800190A8(description_font);
    (void)sub_800119C0(r_u32(0x80065308u));
    w_u8(0x80065904u,stage);
    slot=0u;index=0u;source=0u;
    for(;;)
    {
        record=r_u32(shell3544_table(character)+8u)+(stage<<4u);
        if((sint32)index>=(sint32)r_u16(record+6u) || slot>=6u)break;
        value=(uint32)(sint32)(sint8)r_u8(r_u32(record+8u)+source);
        if(value!=0xFFFFFFFFu)
        {
            w_u8(0x80065676u+slot,value&127u);w_u8(0x8006567Cu+slot,1u);++slot;
        }
        source+=6u;++index;
    }
    while(slot<6u){w_u8(0x80065676u+slot,255u);++slot;}
    return r_u8(r_u32(shell3544_table(character)+8u)+(stage<<4u));
}
