#include "psx.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>

uint32 sub_80011834(void);
uint32 sub_80015F80(uint32);
void sub_800165CC(uint32);
void sub_80019E7C(uint32);
void sub_80019E20(void);
uint32 sub_80019034(uint32,uint32);
uint32 sub_800190A8(uint32);
void sub_8001A0AC(uint32,uint32);
void v8_native_19A58(uint32,uint32,const PSX_RECT *,uint32,uint32,uint32);
uint32 sub_8001D3D8(void);
void v8_native_1D404(uint32,uint32,uint32);
uint32 sub_8001D370(void);
uint32 sub_8001A994(uint32);
uint32 v8_native_1A2CC(const PSX_RECT *,uint32,uint32,uint32);
void v8_native_1A4F8(uint32,uint32);
uint32 sub_8001A584(uint32);
uint32 sub_8001A4AC(uint32,uint32);
uint32 sub_80021C20(uint32);
uint32 sub_8001BDA0(uint32,uint32,uint32);
void sub_8003E598(uint32,uint32);
uint32 sub_8001D708(uint32);
uint32 sub_8001DC1C(uint32);
uint32 sub_8001AC44(uint32,uint32,uint32,uint32);
uint32 sub_8004445C(uint32,uint32,uint32);
uint32 sub_80011A10(void);
uint32 v8_native_1DE08(uint32);
uint32 sub_800120D4(void);
uint32 sub_8001AF48(uint32,uint32);
void sub_8001D490(uint32);
void sub_80045088(uint32);
uint32 sub_800119C0(uint32);
uint32 v8_native_1D9C0(const MATRIX *,uint32);
MATRIX *v8_native_16DA8(MATRIX *);
uint32 v8_native_18D00(uint8 *,uint32,uint8 *,uint32,uint32);
uint32 v8_native_1884C(uint8 *descriptor);
void v8_native_shell_1A30(uint32 base, uint32 count, uint32 text);
void v8_native_shell_bitmap_draw(uint32 base,uint32 asset,uint32 source_rect,uint32 destination_rect,uint32 flags);
void v8_native_shell_DC18(uint32 base,uint32 asset,uint32 x,uint32 y,uint32 flags);

void v8_native_4454C(uint32 voice,uint32 table,uint32 index);
uint32 sub_8002E2BC(uint32 object,uint32 reason,uint32 update);

static void shell4_statbar(uint32 x, uint32 y, uint32 width, uint32 filled, uint32 *background, uint32 *foreground)
{
    int split = (sint32)filled < (sint32)width;
    xport_store_le16((uint8 *)foreground + 16u, (uint16)x);
    xport_store_le16((uint8 *)foreground + 18u, (uint16)y);
    xport_store_le16((uint8 *)foreground + 24u, (uint16)(split ? filled : width));
    DrawPrim(foreground);
    if (split)
    {
        xport_store_le16((uint8 *)background + 16u, (uint16)(x + filled));
        xport_store_le16((uint8 *)background + 18u, (uint16)y);
        xport_store_le16((uint8 *)background + 24u, (uint16)(width - filled));
        DrawPrim(background);
    }
}

static void shell4_missing(uint32 base,uint32 offset)
{
    /* TODO Translate the named observed dependency before executing it */
    fprintf(stderr,"Untranslated Shell 4D24 dependency: base=%08X offset=%X\n",base,offset);
    abort();
}

static void shell4_packet(uint32 base,uint32 *packet,uint32 image,uint32 *texture,uint32 x,uint32 y)
{
    (void)v8_native_18D00((uint8 *)packet,image,(uint8 *)texture,x,y);
}

static void shell4_copy3(uint32 destination,uint32 source)
{
    uint32 a=r_u32(source),b=r_u32(source+4u),c=r_u32(source+8u);
    w_u32(destination,a); w_u32(destination+4u,b); w_u32(destination+8u,c);
}

uint32 sub_800159B4(uint32 path);
uint32 sub_80015A00(void);
uint32 sub_800225D4(uint32 *header,uint32 *remaining);
uint32 sub_8002263C(uint32 bytes,uint32 prepare);
void sub_80045088(uint32 address);
void sub_8001AA38(uint32 object);
void sub_8001A0AC(uint32 rectangle,uint32 color);

void v8_native_shell_223C(uint32 base)
{
    sub_8001A0AC(base+0x43Cu,0u);
}

uint32 v8_native_shell_2264(uint32 base)
{
    uint32 header[2], remaining=0u, allocation, destination=0x800737A0u, tag;
    (void)sub_800159B4(base+0x444u);
    (void)sub_800225D4(header,&remaining);
    remaining=header[1];
    if(header[1]!=0u)
    {
        do
        {
            allocation=sub_800225D4(header,&remaining);
            if(allocation!=0u)
                sub_80045088(allocation);
            else
            {
                tag=((header[0]>>24u)&255u)|((header[0]>>8u)&0xFF00u)|
                    ((header[0]&0xFF00u)<<8u)|(header[0]<<24u);
                if(tag==0x584F4246u)
                {
                    allocation=sub_8002263C(header[1],0u);
                    w_u32(destination,allocation);
                    destination+=4u;
                }
            }
        } while(remaining!=0u);
    }
    return sub_80015A00();
}

void v8_native_shell_2334(uint32 base)
{
    uint32 index,object;
    for(index=0u;index<14u;++index)
    {
        object=r_u32(0x800737A0u+index*4u);
        if(object!=0u) sub_8001AA38(object);
    }
}

uint32 v8_shell_4D24(uint32 base,uint32 excluded,uint32 confirm)
{
    uint32 resource,entry=0u,font,heading,vehicle,model,overlay,row,input,index,value,result;
    uint32 packet_a[8],packet_b[8],texture_a[4],texture_b[4];
    sint32 bars[3]={0,0,0};
    MATRIX matrix;
    PSX_RECT rectangle;
    FUNCTION_MARKER(0x4D24u,"Shell/Shell.dll");
    (void)sub_80011834();
    resource=sub_80015F80(base+0x7B0u);
    (void)v8_native_shell_2264(base);
    sub_800165CC(0u); SetDispMask(0); sub_80019E7C(0u);
    sub_8001A0AC(base+0x43Cu,0u);
    shell4_packet(base,packet_a,resource+r_u32(resource+0x38u),texture_a,374u,100u);
    DrawPrim(packet_a);
    (void)v8_native_1884C((uint8 *)texture_a);
    shell4_packet(base,packet_a,resource+r_u32(resource+0x3Cu),texture_a,0u,0u);
    shell4_packet(base,packet_b,resource+r_u32(resource+0x40u),texture_b,entry,0u);
    w_u16(0x80065A30u,256u); w_u8(0x800659D2u,128u);
restart:
    sub_80019E20();
    value=r_u32(base+0x13388u);
    font=sub_80019034(value+r_u32(value+4u),1u);
    w_u8(font+4u,124u); w_u8(font+5u,96u); w_u8(font+6u,0u);
    sub_8001A0AC(base+0x11E2Cu,0u);
    v8_native_19A58(font,base+0x7C4u,(const PSX_RECT *)psx_addr(base+0x11E2Cu,8u),10u,font,0u);
    (void)sub_800190A8(font);
    v8_native_shell_1A30(base,4u,base+0x7D4u);
    (void)sub_8001D3D8(); v8_native_1D404(0u,base+0x628u,0xFFFFFFu);
    (void)v8_native_16DA8(&matrix);
    {
        uint32 tx=r_u32(base+0x798u), ty=r_u32(base+0x79Cu), tz=r_u32(base+0x7A0u);
        xport_store_le32((uint8 *)&matrix+20u,tx);
        xport_store_le32((uint8 *)&matrix+24u,ty);
        xport_store_le32((uint8 *)&matrix+28u,tz);
    }
    (void)v8_native_1D9C0(&matrix,512u); (void)sub_8001D370();
select_entry:
    (void)sub_8001A994(r_u32(0x800737D4u));
    rectangle=*(PSX_RECT *)psx_addr(base+0x7F8u,8u);
    heading=v8_native_1A2CC(&rectangle,184u,0xFFFFFFECu,0u);
    v8_native_1A4F8(heading,0u);
    index=entry==12u?72u:((sint32)entry<6?68u:64u);
    value=r_u32(heading+20u);
    v8_native_shell_bitmap_draw(base,resource+r_u32(resource+index+4u),value,value,0u);
    v8_native_shell_1A30(base,4u,base+0x7D4u);
    row=base+0x11C68u+entry*20u;
    {
        uint32 item=r_u8(row+13u);
        if(item!=255u)
        {
            uint32 destination=r_u32(heading+20u);
            uint32 dx=r_u8(row+14u),dy=r_u8(row+15u);
            uint32 asset_offset=r_u32(resource+item*4u+4u);
            uint32 rect_x=(uint32)(sint32)(sint16)r_u16(destination);
            uint32 rect_y=(uint32)(sint32)(sint16)r_u16(destination+2u);
            v8_native_shell_DC18(base,resource+asset_offset,rect_x+dx,rect_y+dy,0u);
        }
    }
    DrawSync(0); VSync(0);
    result=sub_8001A584(heading); (void)sub_8001A4AC(heading,result);
    rectangle=*(PSX_RECT *)psx_addr(base+0x800u,8u);
    heading=v8_native_1A2CC(&rectangle,184u,0xFFFFFFECu,0u);
    value=r_u32(base+0x13388u);
    overlay=sub_80019034(value+r_u32(value+8u),1u);
    sub_80019E20(); sub_8001A0AC(base+0x11E24u,0u);
    w_u8(overlay+4u,128u); w_u8(overlay+5u,128u); w_u8(overlay+6u,128u);
    rectangle=*(PSX_RECT *)psx_addr(base+0x11E24u,8u);
    v8_native_19A58(overlay,r_u32(row+8u),&rectangle,2u,overlay,heading);
    rectangle=*(PSX_RECT *)psx_addr(base+0x808u,8u);
    v8_native_19A58(overlay,r_u32(row),&rectangle,2u,overlay,heading);
    w_u8(overlay+4u,124u); w_u8(overlay+5u,99u); w_u8(overlay+6u,22u);
    rectangle=*(PSX_RECT *)psx_addr(base+0x11E24u,8u);
    v8_native_19A58(overlay,base+0x7A8u,&rectangle,0u,overlay,heading);
    v8_native_19A58(overlay,base+0x7ACu,&rectangle,1u,overlay,heading);
    vehicle=sub_80021C20(entry&65535u);
    if((sint32)entry<12)
    {
        w_u32(vehicle,r_u32(vehicle)|8u);
        value=sub_8001BDA0(r_u32(0x800737D4u),11u,heading);
        sub_8003E598(vehicle,value);
    }
    shell4_copy3(vehicle+72u,base+0x810u);
    (void)sub_8001D708(vehicle); (void)sub_8001DC1C(vehicle);
    model=sub_8001AC44(r_u32(0x800737D4u),10u,128u,0u);
    w_u16(r_u32(model+48u)+40u,64u); w_u16(model+64u,0xFC00u);
    shell4_copy3(model+72u,base+0x81Cu);
    (void)sub_8001DC1C(model); (void)sub_8001D708(model);
    v8_native_4454C(1u,r_u32(base+0x1338Cu),4u);
frame:
    (void)sub_80011A10();
    (void)RotMatrixY(16, (MATRIX *)psx_addr(vehicle + 16u, sizeof(MATRIX)));
    value=r_u32(vehicle+100u);
    if(value==0x8002E2BCu)
        (void)sub_8002E2BC(vehicle,0u,0u);
    else if(value!=0u)
        (void)xport_guest_call3(value,vehicle,0u,0u);
    if((r_u32(vehicle)&0x01100000u)==0x00100000u)
    {
        value=r_u16(vehicle+162u);
        index=value<=5120u?3u:(value<=8192u?1u:2u);
        v8_native_4454C(1u,r_u32(base+0x1338Cu),index);
        w_u32(vehicle,r_u32(vehicle)|0x01000000u);
    }
    w_u32(vehicle+44u,0x04000000u); w_u32(vehicle+36u,0x04000000u);
    sub_80019E20();
    for(index=0u;index<3u;++index)
    {
        sint32 delta=(sint32)((r_u8(0x8005EA60u+entry*36u+index+32u)<<1u)-(uint32)bars[index]);
        uint32 next=(uint32)bars[index]+(uint32)(delta< -1?-1:(delta>1?1:delta));
        uint32 half=(uint32)((sint32)next/2);
        bars[index]=(sint32)next;
        shell4_statbar(408u, 106u + 28u * index, 98u, half * 5u, packet_a, packet_b);
    }
    v8_native_1A4F8(heading,0u);
    (void)v8_native_1DE08(vehicle); (void)v8_native_1DE08(model);
    DrawOTag((uint32 *)psx_addr(r_u32(0x80065910u)+0x3FFCu,4u));
    VSync(0); DrawSync(0); result=sub_8001A584(heading);
    (void)sub_800120D4(); SetDispMask(1);
    input=r_u32(0x80065930u);
    if((input&0xA8D00000u)==0u) goto frame;
    if(confirm!=0u && (input&0x08400000u)!=0u)
    {
        w_u32(vehicle+72u,0x04000000u);
        w_u32(vehicle+76u,0x002FF800u-r_u32(vehicle+216u));
        w_u32(vehicle+80u,0x04000000u); w_u16(vehicle+66u,1251u);
        (void)sub_8001D708(vehicle); (void)sub_80011A10();
        v8_native_1A4F8(heading,0u);
        (void)v8_native_1DE08(vehicle); (void)v8_native_1DE08(model);
        DrawOTag((uint32 *)psx_addr(r_u32(0x80065910u)+0x3FFCu,4u));
        DrawSync(0); result=sub_8001A584(heading);
    }
    (void)sub_8001AF48(model,result);
    (void)sub_8001A994(r_u32(vehicle+88u)); sub_8001D490(vehicle);
    (void)sub_800190A8(overlay); (void)sub_8001A4AC(heading,result);
    input=r_u32(0x80065930u);
    do
    {
        entry=(entry+((input>>29u)&1u)+((input&0x80000000u)!=0u?12u:13u))%13u;
    } while((excluded&(1u<<(entry&31u)))!=0u);
    input=r_u32(0x80065930u);
    if((input&0x08D00000u)==0u) goto select_entry;
    index=(input&0x08400000u)!=0u?r_u8(base+0x11C68u+entry*20u+12u):0u;
    (void)sub_8004445C(2u,r_u32(base+0x1338Cu),index);
    if(confirm!=0u && (r_u32(0x80065930u)&0x08400000u)!=0u)
    {
        sub_80019E20(); value=r_u32(base+0x13388u);
        font=sub_80019034(value+r_u32(value+4u),1u);
        sub_8001A0AC(base+0x11E2Cu,0u);
        w_u8(font+4u,124u); w_u8(font+5u,96u); w_u8(font+6u,0u);
        rectangle=*(PSX_RECT *)psx_addr(base+0x11E2Cu,8u);
        v8_native_19A58(font,base+0x828u,&rectangle,10u,font,0u);
        (void)sub_800190A8(font);
        /* TODO 43B4 confirmation keeps original selection mask and resource text */
        shell4_missing(base,0x42D4u);
        if((r_u32(0x80065930u)&0x00100000u)!=0u) goto restart;
    }
    sub_80045088(resource); v8_native_shell_2334(base);
    (void)sub_800119C0(r_u32(0x80065308u));
    return entry;
}
